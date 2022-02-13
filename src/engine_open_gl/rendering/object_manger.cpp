#include "object_manger.h"

object_manger::object_manger() {
	update_projection = false;
	update_cam = false;
	using_custom_shaders = false;
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	common = NULL;
	object_id = 0;

}

object_manger::~object_manger() {

}

void object_manger::draw() {
	common->use();
	common->setMat4("projection", projection);
	common->setMat4("view", view);
	for (int q = 0; q < items.size(); q++) {
		//std::cout << q << std::endl;//useful to findout which model is breaking
		if (items[q]->draw && q != 15) {
			glm::mat4* matrix_temp = items[q]->modelMatrices;
			glBindBuffer(GL_ARRAY_BUFFER, items[q]->buffer);
			if (items[q]->updatemats) {
				glBufferData(GL_ARRAY_BUFFER, items[q]->amount * sizeof(glm::mat4), &matrix_temp[0], GL_STATIC_DRAW);
				items[q]->updatemats = false;
			}

			common->setInt("texture_diffuse1", 0);
			glActiveTexture(GL_TEXTURE0); 
			glBindTexture(GL_TEXTURE_2D, items[q]->model->textures_loaded[0].id);
			for (unsigned int i = 0; i < items[q]->model->meshes.size(); i++)
			{
				glBindVertexArray(items[q]->model->meshes[i].VAO);
				glDrawElementsInstanced(GL_TRIANGLES, items[q]->model->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, items[q]->amount);
				glBindVertexArray(0);
			}
		}
	}

}

void object_manger::init() {
	std::cout << "creating the object manager" << std::endl;

	if (common == NULL) {
		std::cout << "there was no common shader set" << std::endl;
		while (true);
	}


	std::cout << "finished creating the object manager" << std::endl;
}

int object_manger::add_model(std::string name, std::string loc, unsigned int buffer_size, int type, bool draw, Shader* custom_shader) {

	unsigned int buffer;
	unsigned int amount;
	glm::mat4* modelMatrices;
	Model* model;
	std::string* item_name_t = new std::string(name);
	buffer = 0;

	amount = 0;
	modelMatrices = new glm::mat4[buffer_size];
	custom_shader = custom_shader;
	model = new Model(loc);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < model->meshes.size(); i++)
	{
		unsigned int VAO = model->meshes[i].VAO;
		glBindVertexArray(VAO);
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	item* temp = new item;
	temp->buffer_size = buffer_size;
	temp->buffer = buffer;
	temp->amount = amount;
	temp->model = model;
	temp->modelMatrices = modelMatrices;
	temp->custom_shader = custom_shader;
	temp->item_name = item_name_t;
	temp->type = type;
	temp->draw = draw;

	int output = items.size();

	draw_item.push_back(draw);
	items.push_back(temp);

	return output;
}


bool object_manger::increase_buffer_size(int item_index) {
	bool output = false;

	int increase_size = 50;
	//std::cout << "increaseing buffer size for " << item_index << std::endl;
	if (!items.empty() && item_index >= 0 && item_index < items.size()) {
		item* inc = items[item_index];
		if (inc->buffer_size + increase_size <= max_buffer_size) {
			inc->buffer_size += increase_size;
			output = true;
		}
		else {
			if (inc->buffer_size != max_buffer_size) {
				inc->buffer_size = max_buffer_size;
				output = true;
			}
			else {
				std::cout << "item_index was at max_buffer_size: "<< max_buffer_size << std::endl;
			}
		}

		if (output) {
			glm::mat4* modelMatrices = new glm::mat4[inc->buffer_size];

			for (int i = 0; i < inc->amount; i++) {
				modelMatrices[i] = inc->modelMatrices[i];
			}
			delete[] inc->modelMatrices;
			inc->modelMatrices = modelMatrices;
		}
	}
	else {
		std::cout << "item_index out of bounds" << std::endl;
	}

	return output;
}

void object_manger::update_item_matrix(update_pak* data, glm::mat4 given_mat) {

	if (data != NULL && data->item_id < items.size()) {
		//std::cout << "updateing " << data->item_id << ", bufferloc = " << data->buffer_loc << std::endl;
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(data->x_scale, data->y_scale, data->z_scale));
		if (given_mat == glm::mat4(-1.0f)) {
			model = glm::translate(model, glm::vec3(data->x, data->y, data->z));
			model = glm::rotate(model, glm::radians(data->angle), glm::vec3(data->rox_x, data->rox_y, data->rox_z));
		}
		else {
			model = given_mat;
		}
		
		items[data->item_id]->modelMatrices[data->buffer_loc] = model;
		items[data->item_id]->updatemats = true;
		//delete data;//clean mem
	}
	else {
		std::cout << "could not update item, item_id out of range" << std::endl;
	}

}

void object_manger::delete_item_from_buffer(item_info* it) {
	//std::cout << "buffer size " << items[it->item_id]->buffer_size << std::endl;
	//std::cout << "buffer amount " << items[it->item_id]->amount << std::endl;

	if (it == NULL) {
		return;
	}

	if (it->buffer_loc == items[it->item_id]->amount - 1) {//if it is the last one 
		//std::cout << "last one" << std::endl;
		items[it->item_id]->item_data.pop_back();
		items[it->item_id]->amount--;
	}
	else {
		//std::cout << "not last one" << std::endl;
		unsigned int buffer_loc = it->buffer_loc;
		unsigned int buffer_loc_end = items[it->item_id]->amount - 1;
		//std::cout << buffer_loc << std::endl;
		//std::cout << buffer_loc_end << std::endl;
		items[it->item_id]->item_data[buffer_loc] = items[it->item_id]->item_data[buffer_loc_end];
		items[it->item_id]->item_data[buffer_loc]->buffer_loc = buffer_loc;
		items[it->item_id]->item_data.pop_back();
		items[it->item_id]->amount--;
		items[it->item_id]->modelMatrices[buffer_loc] = items[it->item_id]->modelMatrices[buffer_loc_end];
	}
	
	/*delete it;
	it = NULL;*/
}

item_info* object_manger::spawn_item(int type, int x, int y, int z, float angle) {
	glm::mat4 temp =  glm::mat4(1.0f);
	float x_f = float(x * 2);
	float y_f = float(y * 2);
	float z_f = float(z * 2);
	temp = glm::translate(temp, glm::vec3(x_f, y_f, z_f));
	temp = glm::rotate(temp, glm::radians(angle), glm::vec3(0,1,0));
	item_info* output =spawn_item(type, x, y, z, &temp);
	output->angle = angle;

	return output;
}

item_info* object_manger::spawn_item(int type, int x, int y, int z, glm::mat4* given_mat) {
	unsigned int buffer_loc;
	unsigned int item_id;
	bool stackable = false;
	int max_stack_size;
	float x_f = float(x * 2);
	float y_f = float(y * 2);
	float z_f = float(z * 2);
	//	std::cout << "spawning: " << item_type_to_string(type) << std::endl;

			//std::cout << "not a reconized item type, searching through all objects" << std::endl;
	item_id = -1;

	for (int i = 0; i < items.size(); i++) {
		if (items[i]->type == type) {
			item_id = i;
			break;
		}
	}

	if (item_id == -1) {
		std::cout << "could not find obj that item_type" << std::endl;
		return NULL;
	}


	if (items[item_id]->amount >= items[item_id]->buffer_size) {
		//std::cout << "there are too many "<< item_type_to_string(type) << std::endl;
		if (!increase_buffer_size(item_id)) {
			return NULL;
		}
	}


	buffer_loc = items[item_id]->amount;
	items[item_id]->amount++;

	item_info* output = new item_info;
	output->amount = 1;
	//the location on screen
	output->x_m = x_f;
	output->y_m = y_f;
	output->z_m = z_f;

	output->type = type;
	output->x_scale = 1;
	output->y_scale = 1;
	output->z_scale = 1;
	//the location in map
	output->x = x;
	output->y = y;
	output->z = z;

	//output->zone_location = NULL;
	output->item_name = items[item_id]->item_name;
	output->item_id = item_id;
	output->buffer_loc = buffer_loc;
	output->debug_id = object_id;
	object_id++;

	//std::cout << "item at " << x_f << "," << y_f << "," << z_f << std::endl;
	glm::mat4 trans = glm::mat4(1.0f);
	if (given_mat != NULL) {
		trans = *given_mat;
	}
	else {
		trans = glm::translate(trans, glm::vec3(x_f, y_f, z_f));
	}

	items[item_id]->modelMatrices[buffer_loc] = trans;
	items[item_id]->updatemats = true;
	items[item_id]->item_data.push_back(output);
	return output;
}

void object_manger::clear_optimised_items() {

	for (int i = 0; i < optimised_items.size(); i++) {
		optimised_items[i]->draw = false;
		optimised_items[i]->amount = 0;
	}
}

void object_manger::clear_all_object() {

}

std::vector< item*>* object_manger::create_blank_item_list() {
	std::vector< item*>* output = NULL;

	if (items.size() > 0) {
		output = new std::vector< item*>;
		for (int i = 0; i < items.size(); i++) {
			item* temp_item = new item;
			temp_item->model = items[i]->model;
			temp_item->buffer = items[i]->buffer;
			temp_item->buffer_size = items[i]->buffer_size;
			//temp_item->amount = items[i]->amount;
			temp_item->amount = 0;
			//temp_item->modelMatrices = items[i]->modelMatrices;
			temp_item->modelMatrices = new glm::mat4[temp_item->buffer_size];
			temp_item->custom_shader = items[i]->custom_shader;
			//temp_item->item_data = items[i]->item_data;
			temp_item->item_name = items[i]->item_name;
			temp_item->type = items[i]->type;
			temp_item->updatemats = items[i]->updatemats;
			temp_item->draw = false;
			output->push_back(temp_item);
		}
	}

	return output;
}
