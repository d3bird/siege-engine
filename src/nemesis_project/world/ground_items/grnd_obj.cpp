#include "grnd_obj.h"

namespace grnd_items {

	grnd_obj::grnd_obj(int aID, grnd_obj_type aType, int aAmount, int aMax_amount, const loc<int>& alocation):
		ID(aID), type(aType), amount(aAmount), max_amount(aMax_amount),
		rendering_model(NULL), location(alocation)
	{
	}

	grnd_obj::~grnd_obj()
	{
	}

	void grnd_obj::set_type(grnd_obj_type aType) {
		if (type != aType) {
			//update the proporties of this object
			type = aType;
		}
	}

	void grnd_obj::set_rendering_model(rendering::item_info* model) {
		if (model != NULL) {
			rendering_model = model;
		}
	}

	rendering::item_info* grnd_obj::get_model() {
		return rendering_model;
	}

	int grnd_obj::get_ID() {
		return ID;
	}

	loc<int> grnd_obj::get_location() {
		return location;
	}

	int grnd_obj::get_amount() {
		return amount;
	}

	int grnd_obj::get_max_amount() {
		return max_amount;
	}

	grnd_obj_type grnd_obj::get_type() {
		return type;
	}

	int grnd_obj::operator+=(int add) {
		int output = 0;
		amount += add;
		if (amount > max_amount) {
			output = (amount - max_amount);
			amount = max_amount;
		}
		return output;
	}

	int grnd_obj::operator-=(int subtrack) {
		int output = 0;
		amount -= subtrack;
		if (amount < 0) {
			output = amount;
			amount = 0;
		}
		return output;
	}

	int grnd_obj::operator-(int subtrack) {
		int output = 0;
		amount -= subtrack;
		if (amount < 0) {
			output = amount;
			amount = 0;
		}
		return output;
	}

	int grnd_obj::operator+(int add) {
		int output = 0;
		amount += add;
		if (amount > max_amount) {
			output = (amount - max_amount);
			amount = max_amount;
		}
		return output;
	}

	bool grnd_obj::operator==(const grnd_obj& other) {
		return ID == other.ID;
	}

	bool grnd_obj::operator==(int other_id) {
		return ID == other_id;
	}

}