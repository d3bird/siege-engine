#include "engine.h"


engine::engine() {

    text_render = NULL;
    Time = NULL;
    gui = NULL;
    ADM = NULL;
    OBJM = NULL;
    ANIM = NULL;
    ANIM_shader = NULL;
    single = false;
    update_lights = true;

    render_text = true;
    draw_speakers = false;
    draw_lights_debug = false;
    update_projection = false;

    online = false;
    LM = NULL;
    time_change = NULL;
}

engine::~engine(){
    OBJM->clear_all_object();
    delete OBJM;
    delete ADM;
}

//draw with a single light source
void engine::draw_single() {

	//std::cout << "drawling sky" << std::endl;

	//std::cout << "setting lighting " << std::endl;
	lighting_in->use();
	lighting_in->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	//lighting_in->setVec3("lightPos", Sky->get_light_loc());
	lighting_in->setVec3("lightPos", glm::vec3(10,10,10));
	//lighting_in->setVec3("lightColor", 0.0f, 1.0f, 1.0f);
	lighting_in->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

	//std::cout << "drawling city" << std::endl;
	//City->set_cam(view);
	//City->draw();

    OBJM->set_cam(view);
    OBJM->draw();
    ANIM->draw();
}

//draw with deferred shadering
void engine::draw_deferred() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    shaderGeometryPass->use();
    shaderGeometryPass->setMat4("projection", projection);
    shaderGeometryPass->setMat4("view", view);

    //draw the entire scene
    //City->set_cam(view);
    //City->draw();
    OBJM->set_cam(view);

    switch (engine_data->draw_optimize)
    {
    case RENDERING_QUE:
      ///  OBJM->draw_rendering_que();
      //  break;
    case DRAW_EVERYTHING:
    case ONY_GROUP:
    case LINKED_GROUP:
    default:
        OBJM->draw();
      
        break;
    }
     
   // OBJM->set_look_dir(Player->get_direction());

    //OBJM->set_look_dir(Player->get_direction());
  //  OBJM->draw_optimised();
    //OBJM->draw_height_map_degbug();
   // OBJM->draw_pathfinding_map_degbug();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

  //  std::cout << "lighting tests" << std::endl;

    // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
    // -----------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderLightingPass->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    // send light relevant uniforms
    if (LM->need_to_update()) {

        std::cout << "lighting upadte was triggered" << std::endl;

        if (LM->get_current_scene() != NULL) {
            lightColors = LM->get_current_scene()->light_col;
            lightPositions = LM->get_current_scene()->light_pos;
        }

        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
            shaderLightingPass->setVec3("lights[" + std::to_string(i) + "].Position", *(lightPositions[i]));
            shaderLightingPass->setVec3("lights[" + std::to_string(i) + "].Color", *(lightColors[i]));
            // update attenuation parameters and calculate radius
            float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
            float linear = 0.22f;
            float quadratic = 0.2f;
            shaderLightingPass->setFloat("lights[" + std::to_string(i) + "].Linear", linear);
            shaderLightingPass->setFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
            const float maxBrightness = std::fmaxf(std::fmaxf(lightColors[i]->r, lightColors[i]->g), lightColors[i]->b);
            float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
            shaderLightingPass->setFloat("lights[" + std::to_string(i) + "].Radius", radius);
        }
       // update_lights = false;
        LM->set_trigger_update(false);
    }
    shaderLightingPass->setVec3("viewPos", cam_pos);
    // finally render quad
    renderQuad();

    // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
    // ----------------------------------------------------------------------------------
    glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
    // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
    // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
    // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
    glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. render lights on top of scene
    // --------------------------------
    if (draw_lights_debug || draw_speakers) {
        shaderLightBox->use();
        shaderLightBox->setMat4("projection", projection);
        shaderLightBox->setMat4("view", view);
        if (draw_lights_debug) {
            for (unsigned int i = 0; i < lightPositions.size(); i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, *(lightPositions[i]));
                model = glm::scale(model, glm::vec3(0.125f));
                shaderLightBox->setMat4("model", model);
                shaderLightBox->setVec3("lightColor", *(lightColors[i]));
                renderCube();
            }
        }
        if(draw_speakers){
            for (unsigned int i = 0; i < speakers_locs.size(); i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, speakers_locs[i]);
                model = glm::scale(model, glm::vec3(0.125f));
                shaderLightBox->setMat4("model", model);
                shaderLightBox->setVec3("lightColor",glm::vec3(0.0f, 1.0f,0.0));
                renderCube();
            }
        }
    }


    ADM->draw_speaker_locations();

    if (ANIM_shader != NULL) {
        ANIM_shader->use();
        ANIM_shader->setMat4("view", view);
        ANIM_shader->setMat4("projection", projection);
        ANIM->draw();
    }

    switch (engine_data->gui_draw_type)
    {
    case DRAW_ENGINES_GUI:
        gui->draw();
        break;
    case DRAW_SCENE_GUI:
        break;
    case DRAW_BOTH_GUI:
        gui->draw();
        break;
    case DRAW_NONE_GUI:
    default:
        break;
    }
   
    //daw objects that need to be affected by blending
    if (render_text) {
        glEnable(GL_BLEND);
        text_render->draw();
        glDisable(GL_BLEND);
    }
}

void engine::draw_only_animations() {
    ANIM_shader->use();
    ANIM_shader->setMat4("view", view);
    ANIM_shader->setMat4("projection", projection);
    ANIM->draw();
}

void engine::draw_all_objects() {
    lighting_in->use();
    lighting_in->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    //lighting_in->setVec3("lightPos", Sky->get_light_loc());
    lighting_in->setVec3("lightPos", glm::vec3(10, 10, 10));
    //lighting_in->setVec3("lightColor", 0.0f, 1.0f, 1.0f);
    lighting_in->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
   // lighting_in->setMat4()
    OBJM->set_cam(view);
    OBJM->draw();
}

void engine::update() {

    
    ADM->update();
    ANIM->update(*time_change);

}

void engine::change_projection(glm::mat4 i) {
    projection = i;
    update_projection = true;
    if (shaderGeometryPass != NULL) {
        shaderGeometryPass->setMat4("projection", i);
    }
    if (shaderLightBox != NULL) {
        shaderLightBox->setMat4("projection", i);
    }

    OBJM->set_projection(i);
    ANIM_shader->setMat4("projection", i);
   // City->set_projection(projection);
    //Sky->set_projection(projection);
    //lighting_in
}

void engine::init(GUI* g, engine_obj* eng, bool ser) {
    std::cout << "initing the init " << std::endl;

    gui = g;
    lighting_in = new rendering::Shader("lighting_instances.vs", "lighting_instances.fs");
    
    engine_data = eng;

    if (ANIM == NULL) {
        std::cout << "animation_manager was not set beforehand, setting now" << std::endl;
        ANIM = engine_data->ANIM;
        if (ANIM == NULL) {
            std::cout << "animation_manager failed to set" << std::endl;
        }
        ANIM_shader = ANIM->get_shader();
        if (ANIM_shader == NULL) {
            std::cout << "failed to get shader for the animation" << std::endl;
        }
    }
    time_change = engine_data->time->get_time_change_static();
    std::cout << "creating the lighting" << std::endl;
    lighting_init();

    std::cout << "creating the text rendering" << std::endl;

    if (render_text) {
        if (text_render == NULL) {
            text_render = new text_engine();
            text_render->set_time(Time);
            text_render->set_projection(projection);
            text_render->set_cam(view);
            text_render->init();
        }
        else {
            std::cout << "using premade text render" << std::endl;
        }
    }

    std::cout << "creating the audio" << std::endl;

    ADM = new audio_syst::audio_manger();
    ADM->init();

    eng->ADM = ADM;

    std::cout << "creating the object manager" << std::endl;

    OBJM = new rendering::object_manger();
    OBJM->set_projection(projection);
    OBJM->set_cam(view);

    if (single) {
        OBJM->set_standered_shader(lighting_in);
    }
    else {
        OBJM->set_standered_shader(shaderGeometryPass);
    }

    OBJM->init();
	
    eng->OBJM = OBJM;


    if (gui != NULL) {
        gui->set_OBJM(OBJM);
    }

    draw_speakers = ADM->draw_speaker_locations();
    speakers_locs = ADM->get_speaker_locations();
   
	std::cout << "finished initing objects" << std::endl;
    std::cout << std::endl;

    print_engine_data(engine_data);

}

void engine::lighting_init() {

    std::cout << "creating the lighting manager" << std::endl;
    //the lighting manger controls the lighting scenes, colors and locations
    //while this class handles the rendering of the lights on the different objects
    LM = new light_mgr(NR_LIGHTS);
    LM->init();

    std::cout << "creating SHADERS" << std::endl;

    shaderGeometryPass = new rendering::Shader("g_buffer.vs", "g_buffer.fs");
    shaderLightingPass = new rendering::Shader("deferred_shading.vs", "deferred_shading.fs");
    shaderLightBox = new rendering::Shader("deferred_light_box.vs", "deferred_light_box.fs");

    std::cout << "creating " << std::endl;


    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 

    glDrawBuffers(3, attachments);
    // create and attach depth buffer (renderbuffer)

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // lighting info
    // -------------

    std::cout << "creating LIGHITNG INFOR" << std::endl;


    srand(13);
    int x = 1;
    for (unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        // calculate slightly random offsets
        float xPos = (float)x;
        x += 8;
        float yPos = 4.0f;
        float zPos = 1.0f;
       // lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
        float rColor;
        float gColor;
        float bColor;
        if (i == 0) {
            rColor = 0.0f;
            gColor = 0.0f;
            bColor = 1.0f;

        }
        else {
            rColor = (float) ((rand() % 100) / 200.0f) + 0.5f; // between 0.5 and 1.0
            gColor = (float)((rand() % 100) / 200.0f) + 0.5f; // between 0.5 and 1.0
            bColor = (float)((rand() % 100) / 200.0f) + 0.5f; // between 0.5 and 1.0
        }

        // also calculate r-andom color

       // lightColors.push_back(glm::vec3(rColor, gColor, bColor));

        LM->add_def_light(glm::vec3(rColor, gColor, bColor), glm::vec3(xPos, yPos, zPos));
    }
    LM->print_info();

    if (LM->get_current_scene() != NULL) {
        lightColors = LM->get_current_scene()->light_col;
        lightPositions = LM->get_current_scene()->light_pos;
    }

    if (gui != NULL) {
        gui->set_LM(LM);
    }

    // shader configuration
    // --------------------
    shaderLightingPass->use();
    shaderLightingPass->setInt("gPosition", 0);
    shaderLightingPass->setInt("gNormal", 1);
    shaderLightingPass->setInt("gAlbedoSpec", 2);


}

void engine::renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void engine::renderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}