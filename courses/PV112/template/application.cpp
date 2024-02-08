#include "application.hpp"

#include <memory>
#include <iostream>
#include "glm/ext.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using std::make_shared;

GLuint load_texture_2d(const std::filesystem::path filename)
{
    int width, height, channels;

    unsigned char *data = stbi_load(filename.generic_string().data(), &width, &height, &channels, 4);

    GLuint texture;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);

    glTextureStorage2D(texture, (GLsizei)std::log2(width), GL_RGBA8, width, height);

    glTextureSubImage2D(texture,
                        0,                         //
                        0, 0,                      //
                        width, height,             //
                        GL_RGBA, GL_UNSIGNED_BYTE, //
                        data);

    stbi_image_free(data);

    glGenerateTextureMipmap(texture);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

Application::Application(int initial_width, int initial_height, std::vector<std::string> arguments)
    : PV112Application(initial_width, initial_height, arguments)
{
    renderer = Renderer::Renderer();
    this->width = initial_width;
    this->height = initial_height;

    images_path = lecture_folder_path / "images";
    objects_path = lecture_folder_path / "objects";

    // --------------------------------------------------------------------------
    //  Load/Create Objects
    // --------------------------------------------------------------------------
    geometries.push_back(make_shared<Sphere>());
    // You can use from_file function to load a Geometry from .obj file
    // geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "tank.obj")));
    geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "OgreOBJ.obj")));
    geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "ground.obj")));
    geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "tree_winter.obj")));
    geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "oakTree.obj")));

    sphere = geometries[0];
    userChar = geometries[1];
    enemyChar = geometries[1];
    ground = geometries[2];
    sky = geometries[2];
    deadTree = geometries[3];
    tree = geometries[4];

    gear_texture = load_texture_2d(images_path / "gear.png");
    ground_texture = load_texture_2d(images_path / "ground.png");
    sky_texture = load_texture_2d(images_path / "sky.jpg");
    ogre_texture = load_texture_2d(objects_path / "SkinColorMostro_COLOR.png");
    deadTree_texture = load_texture_2d(objects_path / "trees-2106123_1920.jpg");
    tree_texture = load_texture_2d(objects_path / "10445_Oak_Tree_v1_diffuse.jpg");

    // --------------------------------------------------------------------------
    // Initialize UBO Data
    // --------------------------------------------------------------------------
    std::cout << glm::to_string(camera.get_eye_position()) << std::endl;
    camera_ubo.position = glm::vec4(camera.get_eye_position(), 1.0f);
    std::cout << glm::to_string(camera_ubo.position) << std::endl;
    camera_ubo.projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.01f, 500.0f);
    camera_ubo.view = glm::lookAt(camera.get_eye_position(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));

    light_ubo.position = glm::vec4(3.0f, 2.0f, 0.0f, 1.0f);
    light_ubo.ambient_color = glm::vec4(1.0f);
    light_ubo.diffuse_color = glm::vec4(1.0f);
    light_ubo.specular_color = glm::vec4(1.0f);

    objects_ubos.push_back({.model_matrix = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), glm::vec3(light_ubo.position)),
                            .ambient_color = glm::vec4(0.0f),
                            .diffuse_color = glm::vec4(1.0f),
                            .specular_color = glm::vec4(1.0f)});
    objects_ubos.push_back({.model_matrix = glm::scale(glm::mat4(1.f), glm::vec3(0.1f)),
                            .ambient_color = glm::vec4(0.0f),
                            .diffuse_color = glm::vec4(1.0f),
                            .specular_color = glm::vec4(1.0f)});
    // User character(closer to screen, rotated)
    glm::vec4 userCharPos = glm::vec4(-1.0f, -0.1f, 7.5f, 1.f);
    // glm::vec4 userCharPos = glm::vec4(0.f, 0.f, 0.f, 1.f);
    glm::vec3 userCharPos3 = glm::vec3(userCharPos) * userCharPos.w;
    // glm::vec4 enemyCharPos = glm::vec4(0.f, 0.f, 0.f, 1.f);
    glm::vec4 enemyCharPos = glm::vec4(2.f, -0.1f, 2.5f, 1.f);
    glm::vec3 enemyCharPos3 = glm::vec3(enemyCharPos) * enemyCharPos.w;

    glm::mat4 charTranslation = glm::translate(glm::mat4(1.f), userCharPos3);
    glm::mat4 charRotation = glm::inverse(glm::lookAt(glm::vec3(0.f), glm::normalize(userCharPos3 - enemyCharPos3), glm::vec3(0.f, 1.f, 0.f)));
    glm::mat4 charScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    glm::mat4 charMatrix = charTranslation * charRotation * charScale;
    std::cout << glm::to_string(charMatrix) << std::endl;
    objects_ubos.push_back({.model_matrix = charMatrix,
                            .ambient_color = glm::vec4(0.0f),
                            .diffuse_color = glm::vec4(1.0f),
                            .specular_color = glm::vec4(0.0f)});

    // Enemy character(closer to screen, rotated)
    glm::mat4 enemyCharTranslation = glm::translate(glm::mat4(1.f), enemyCharPos3);
    glm::mat4 enemyCharRotation = glm::inverse(glm::lookAt(glm::vec3(0.f), glm::normalize(enemyCharPos3 - userCharPos3), glm::vec3(0.f, 1.f, 0.f)));
    glm::mat4 enemyCharScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    glm::mat4 enemyCharMatrix = enemyCharTranslation * enemyCharRotation * enemyCharScale;
    std::cout << glm::to_string(enemyCharMatrix) << std::endl;
    objects_ubos.push_back({.model_matrix = enemyCharMatrix,
                            .ambient_color = glm::vec4(0.f),
                            .diffuse_color = glm::vec4(1.f),
                            .specular_color = glm::vec4(0.f)});

    // Ground
    glm::mat4 groundTranslation = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -0.5f, 0.f));
    glm::mat4 groundScale = glm::scale(glm::mat4(1.0f), glm::vec3(300.f));
    objects_ubos.push_back({.model_matrix = groundTranslation * groundScale,
                            .ambient_color = glm::vec4(0.8f),
                            .diffuse_color = glm::vec4(1.f),
                            .specular_color = glm::vec4(0.f)});

    glm::mat4 skyTranslation = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -6.f));
    glm::mat4 skyScale = glm::scale(glm::mat4(1.f), glm::vec3(50.f));
    glm::mat4 skyRotation = glm::rotate(glm::mat4(1.f), glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f));
    objects_ubos.push_back({.model_matrix = skyTranslation * skyScale * skyRotation,
                            .ambient_color = glm::vec4(0.8f),
                            .diffuse_color = glm::vec4(1.f),
                            .specular_color = glm::vec4(0.0f)});

    // --------------------------------------------------------------------------
    // Trees
    // --------------------------------------------------------------------------
    
    // float min = 0.f;
    // float max = -10.f;

    // std::vector<ObjectUBO> deadTreeObjects;
    // std::vector<ObjectUBO> treeObjects;
    
    
    for (size_t i = 0; i < 100; i++)
    {
        glm::mat4 treeScaling = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
        // std::cout << static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f) * -4.f << std::endl;
        float xCoord = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f) * -10.f;
        float yCoord = 0.f;
        float zCoord = -(sinf(float(i)) + 1.f) * 10.f;
        if (i % 2 == 0) {
            xCoord = -xCoord;
        }
        if (i % 5 == 0 && zCoord < -5) {
            float randScale = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f) * 3.f;
            treeScaling = glm::scale(glm::mat4(1.f), glm::vec3(randScale));
            yCoord = randScale / 3.f;
        }
        // if (zCoord > -4.4)
        // {/
            glm::mat4 deadTreeTranslation = glm::translate(glm::mat4(1.f), glm::vec3(xCoord, yCoord, zCoord));
            objects_ubos.push_back({.model_matrix = deadTreeTranslation * treeScaling,
                                       .ambient_color = glm::vec4(0.8f),
                                       .diffuse_color = glm::vec4(1.f),
                                       .specular_color = glm::vec4(0.0f)});
        // } else {
            glm::mat4 treeTranslation = glm::translate(glm::mat4(1.f), glm::vec3(-xCoord, yCoord, zCoord));
            glm::mat4 treeRotation = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(-1.f, 0.f, 0.f));
            objects_ubos.push_back({.model_matrix = treeTranslation * treeScaling * treeRotation,
                                    .ambient_color = glm::vec4(0.8f),
                                    .diffuse_color = glm::vec4(1.f),
                                    .specular_color = glm::vec4(0.0f)});
        // }        
    }
    // std::cout << "Min: " << min << ", Max: " << max << std::endl;
    // objects_ubos.insert(objects_ubos.end(), deadTreeObjects.begin(), deadTreeObjects.end());
    // objects_ubos.insert(objects_ubos.end(), treeObjects.begin(), treeObjects.end());
    // deadTreeCount = deadTreeObjects.size();

    // --------------------------------------------------------------------------
    // Cone lights above characters
    // --------------------------------------------------------------------------
    glm::vec3 coneLightAmbient = glm::vec3(0.6f);
    userCharLight.position = userCharPos + glm::vec4(0.f, 2.f, 0.f, 0.f); // position light above character
    userCharLight.direction = glm::vec4(0.f, -1.f, 0.f, 0.f);             // look down the y axis
    userCharLight.angle = cosf(glm::radians(30.f));
    userCharLight.attenuation = 1.2f;
    userCharLight.ambient_color = glm::vec4(0.0f);
    userCharLight.diffuse_color = glm::vec4(1.0f);
    userCharLight.specular_color = glm::vec4(0.0f);

    coneLights.push_back(userCharLight);

    enemyCharLight.position = enemyCharPos + glm::vec4(0.f, 2.f, 0.f, 0.f); // position light above character
    enemyCharLight.direction = glm::vec4(0.f, -1.f, 0.f, 0.f);              // look down the y axis
    enemyCharLight.angle = cosf(glm::radians(30.f));
    enemyCharLight.attenuation = 1.2f;
    enemyCharLight.ambient_color = glm::vec4(coneLightAmbient, 1.0f);
    enemyCharLight.diffuse_color = glm::vec4(1.0f);
    enemyCharLight.specular_color = glm::vec4(0.0f);

    coneLights.push_back(enemyCharLight);

    // --------------------------------------------------------------------------
    // Fog
    // --------------------------------------------------------------------------
    fog_ubo.color = glm::vec4(0.4, 0.4, 0.4, 1.0);
    fog_ubo.density = 0.6f;
    fog_ubo.start = 2.5f;
    fog_ubo.end = 10.f;

    // --------------------------------------------------------------------------
    // Create Buffers
    // --------------------------------------------------------------------------
    glCreateBuffers(1, &camera_buffer);
    glNamedBufferStorage(camera_buffer, sizeof(CameraUBO), &camera_ubo, GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &light_buffer);
    glNamedBufferStorage(light_buffer, sizeof(LightUBO), &light_ubo, GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &objects_buffer);
    glNamedBufferStorage(objects_buffer, sizeof(ObjectUBO) * objects_ubos.size(), objects_ubos.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &lights_buffer);
    glNamedBufferStorage(lights_buffer, sizeof(ConeLightUBO) * coneLights.size(), coneLights.data(), GL_DYNAMIC_STORAGE_BIT);
    glCreateBuffers(1, &fog_buffer);
    glNamedBufferStorage(fog_buffer, sizeof(FogUBO), &fog_ubo, GL_DYNAMIC_STORAGE_BIT);
    compile_shaders();
}

Application::~Application()
{
    delete_shaders();

    glDeleteBuffers(1, &camera_buffer);
    glDeleteBuffers(1, &light_buffer);
    glDeleteBuffers(1, &objects_buffer);
    glDeleteBuffers(1, &lights_buffer);
    glDeleteBuffers(1, &fog_buffer);
}

// ----------------------------------------------------------------------------
// Methods
// ----------------------------------------------------------------------------

void Application::delete_shaders()
{
    if (!initedPrograms)
    {
        return;
    }
    GLint param = 0;
    glGetProgramiv(main_program, GL_LINK_STATUS, &param);
    if (param == GL_TRUE)
    {
        glDeleteProgram(main_program);
    }
    // glGetProgramiv(lights_program, GL_LINK_STATUS, &param);
    // if (param == GL_TRUE)
    // {
    // glDeleteProgram(lights_program);
    // }
}

void Application::compile_shaders()
{
    delete_shaders();
    main_program = create_program(lecture_shaders_path / "main.vert", lecture_shaders_path / "main.frag");
    // lights_program = create_program(lecture_shaders_path / "lights.vert", lecture_shaders_path / "lights.frag");
    std::cout << "Shaders are reloaded." << std::endl;
}

void Application::update(float delta) {}

void Application::render()
{

    // --------------------------------------------------------------------------
    // Update UBOs
    // --------------------------------------------------------------------------
    // Camera
    camera_ubo.position = glm::vec4(camera.get_eye_position(), 1.0f);
    camera_ubo.projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 500.0f);
    camera_ubo.view = glm::lookAt(camera.get_eye_position(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glNamedBufferSubData(camera_buffer, 0, sizeof(CameraUBO), &camera_ubo);

    // --------------------------------------------------------------------------
    // Draw scene
    // --------------------------------------------------------------------------
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);


    // Draw objects
    // glUseProgram(main_program);
    GLint param = 0;

    switch (gameState.currentState)
    {
    case GAME_MENU:
    
        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configure fixed function pipeline
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        camera.set_eye_position(0.f, glm::radians(5.f), 10.f);
        break;
    case PLAY_MENU:
    case PLAY_VS_AI:
        
        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configure fixed function pipeline
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glUseProgram(main_program);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, camera_buffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, light_buffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, lights_buffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, 5, fog_buffer);
        glUniform1i(glGetUniformLocation(main_program, "has_2Dtexture"), true);
        glBindTextureUnit(3, ogre_texture);

        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 2 * 256, sizeof(ObjectUBO));
        userChar->draw();

        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 3 * 256, sizeof(ObjectUBO));
        enemyChar->draw();

        glBindTextureUnit(3, ground_texture);
        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 4 * 256, sizeof(ObjectUBO));
        ground->draw();

        glBindTextureUnit(3, sky_texture);
        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 5 * 256, sizeof(ObjectUBO));
        // sky->draw();

        for (size_t i = 0; i < 100; i++) {
            glBindTextureUnit(3, deadTree_texture);
            glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, (6 + i * 2) * 256, sizeof(ObjectUBO));
            deadTree->draw();
        // }
        // for (size_t i = 0; i < 40 - deadTreeCount; i++) {
            glBindTextureUnit(3, tree_texture);
            glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, (7 + i * 2) * 256, sizeof(ObjectUBO));
            tree->draw();
        }
        break;
    }
}

void Application::render_ui()
{
    switch (gameState.currentState)
    {
    case GAME_MENU:
        renderer.menuRender(width, height, &gameState);
        break;
    case GAME_EXIT:
        this->~Application();
        break;
    case PLAY_VS_AI:
        // TODO add other textures for icon health and other stuff?
        renderer.aiPlayRender(width, height, &gameState, gear_texture);
        break;
    case HOW_TO_PLAY:
        renderer.howToPlayRender(width, height, &gameState);
        break;
    case PLAY_MENU:
        renderer.playMenuRender(width, height, &gameState);
        break;
    }
}

// ----------------------------------------------------------------------------
// Input Events
// ----------------------------------------------------------------------------

void Application::on_resize(int width, int height)
{
    // Calls the default implementation to set the class variables.
    PV112Application::on_resize(width, height);
}

void Application::on_mouse_move(double x, double y)
{
    camera.on_mouse_move(x, y);
}
void Application::on_mouse_button(int button, int action, int mods)
{
    camera.on_mouse_button(button, action, mods);
}
void Application::on_key_pressed(int key, int scancode, int action, int mods)
{
    // Calls default implementation that invokes compile_shaders when 'R key is hit.
    PV112Application::on_key_pressed(key, scancode, action, mods);
}