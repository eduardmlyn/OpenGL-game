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
    // stbi_info(filename.generic_string().data(), &width, &height, &channels);
    // std::cout << width << ", " << height << ", " << (GLsizei)std::log2(width) << "\n";

    unsigned char *data = stbi_load(filename.generic_string().data(), &width, &height, &channels, 4);

    GLuint texture;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    // std::cout << width << ", " << height << ", " << (GLsizei)std::log2(width) << "\n";

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
    // geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "bunny.obj")));
    geometries.push_back(make_shared<Geometry>(Geometry::from_file(objects_path / "tank.obj")));

    sphere = geometries[0];
    // bunny = geometries[1];
    userChar = geometries[1];
    enemyChar = geometries[1];

    // marble_texture = load_texture_2d(images_path / "bunny.jpg");
    // healer_texture = load_texture_2d(images_path / "healer.jpg"); // TODO try to use the mtl file for healer, should actually change the color and apply the texture correctly
    gear_texture = load_texture_2d(images_path / "gear.png");

    // --------------------------------------------------------------------------
    // Initialize UBO Data
    // --------------------------------------------------------------------------
    camera_ubo.position = glm::vec4(camera.get_eye_position(), 1.0f);
    camera_ubo.projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.01f, 500.0f);
    camera_ubo.view = glm::lookAt(camera.get_eye_position(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));

    // std::cout << glm::to_string(camera_ubo.view);
    light_ubo.position = glm::vec4(0.0f, 3.0f, 2.0f, 1.0f);
    light_ubo.ambient_color = glm::vec4(1.0f);
    light_ubo.diffuse_color = glm::vec4(2.0f, 2.0f, 1.0f, 1.0f);
    light_ubo.specular_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    objects_ubos.push_back({.model_matrix = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)), glm::vec3(light_ubo.position)),
                            .ambient_color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
                            .diffuse_color = glm::vec4(0.0),
                            .specular_color = glm::vec4(0.0f)});
    // User character(closer to screen, rotated)
    glm::vec3 userCharPos = glm::vec3(-1.f, 0.f, 7.5f);
    glm::vec3 enemyCharPos = glm::vec3(2.f, 0.f, 2.5f);
    glm::mat4 charTranslation = glm::translate(glm::mat4(1.f), userCharPos);
    glm::mat4 charRotation = glm::inverse(glm::lookAt(glm::vec3(0.f), glm::normalize(userCharPos - enemyCharPos), glm::vec3(0.f, 1.f, 0.f))); // glm::rotate(glm::mat4(1.f), glm::radians(155.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 charScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    glm::mat4 charMatrix = charTranslation * charRotation * charScale;
    std::cout << glm::to_string(charMatrix) << std::endl;
    objects_ubos.push_back({.model_matrix = charMatrix,
                            .ambient_color = glm::vec4(0.0f),
                            .diffuse_color = glm::vec4(1.0f),
                            .specular_color = glm::vec4(0.0f)});
    // Enemy character(closer to screen, rotated)

    charTranslation = glm::translate(glm::mat4(1.f), enemyCharPos);
    charRotation = glm::inverse(glm::lookAt(glm::vec3(0.f), glm::normalize(enemyCharPos - userCharPos), glm::vec3(0.f, 1.f, 0.f))); // glm::rotate(glm::mat4(1.f), glm::radians(-40.f), glm::vec3(0.f, 1.f, 0.f));
    charScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    charMatrix = charTranslation * charRotation * charScale;
    std::cout << glm::to_string(charMatrix) << std::endl;
    objects_ubos.push_back({.model_matrix = charMatrix,
                            .ambient_color = glm::vec4(0.f),
                            .diffuse_color = glm::vec4(1.f),
                            .specular_color = glm::vec4(0.f)});

    // --------------------------------------------------------------------------
    // Cone lights above characters
    // --------------------------------------------------------------------------
    userCharLight.lightUbo.position = glm::vec4(userCharPos.x, 1.5f, userCharPos.z, 1.f);
    userCharLight.direction = glm::vec4(0.f, -1.f, 0.f, 1.f);
    userCharLight.angle = cosf(glm::radians(45.f));
    userCharLight.lightUbo.ambient_color = glm::vec4(1.0f);
    userCharLight.lightUbo.diffuse_color = glm::vec4(1.0f);
    userCharLight.lightUbo.specular_color = glm::vec4(1.0f);

    coneLights.push_back(userCharLight);
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
    compile_shaders();
}

Application::~Application()
{
    delete_shaders();

    glDeleteBuffers(1, &camera_buffer);
    glDeleteBuffers(1, &light_buffer);
    glDeleteBuffers(1, &objects_buffer);
    glDeleteBuffers(1, &lights_buffer);
}

// ----------------------------------------------------------------------------
// Methods
// ----------------------------------------------------------------------------

void Application::delete_shaders()
{
    GLint param = 0;
    glGetProgramiv(main_program, GL_LINK_STATUS, &param);
    if (param == GL_TRUE)
    {
        glDeleteProgram(main_program);
    }
    glGetProgramiv(lights_program, GL_LINK_STATUS, &param);
    if (param == GL_TRUE)
    {
        glDeleteProgram(lights_program);
    }
}

void Application::compile_shaders()
{
    delete_shaders();
    main_program = create_program(lecture_shaders_path / "main.vert", lecture_shaders_path / "main.frag");
    lights_program = create_program(lecture_shaders_path / "lights.vert", lecture_shaders_path / "lights.frag");
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
    camera_ubo.projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);
    camera_ubo.view = glm::lookAt(camera.get_eye_position(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glNamedBufferSubData(camera_buffer, 0, sizeof(CameraUBO), &camera_ubo);

    // --------------------------------------------------------------------------
    // Draw scene
    // --------------------------------------------------------------------------
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configure fixed function pipeline
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Draw objects
    // glUseProgram(main_program);
    GLint param = 0;

    // TODO Change rendering functions based on the game state
    switch (gameState.currentState)
    {
    case GAME_MENU:
        camera.set_eye_position(0.f, glm::radians(5.f), 10.f);
        // renderer.menuRender(menu_program);
        break;
    case PLAY_MENU: // TODO think about the pvp play similarly to ai play, maybe have it fall down in rendering as well
    case PLAY_VS_AI:
        glUseProgram(main_program);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, camera_buffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, light_buffer);

        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 0 * 256, sizeof(ObjectUBO));

        sphere->draw();

        glGetProgramiv(lights_program, GL_LINK_STATUS, &param);
        std::cout << param << std::endl;
        // glUseProgram(lights_program);
        // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, lights_buffer);

        sphere->draw_instanced(1);
        // sphere->bind_vao();
        // glDrawElementsInstanced(sphere->mode, sphere->draw_elements_count, GL_UNSIGNED_INT, nullptr, coneLights.size());
        // glBindBufferBase(GL_UNIFORM_BUFFER, 0, camera_buffer);
        // glBindBufferBase(GL_UNIFORM_BUFFER, 1, light_buffer);
        // glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 2 * 256, sizeof(ObjectUBO));
        // glUniform1i(glGetUniformLocation(main_program, "has_texture"), true);
        // objTest->draw();
        glUseProgram(main_program);

        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 1 * 256, sizeof(ObjectUBO));

        glUniform1i(glGetUniformLocation(main_program, "has_texture"), false);
        // glBindTextureUnit(3, healer_texture);
        // GLint textureWidth;
        // glGetTextureLevelParameteriv(healer_texture, 0, GL_TEXTURE_WIDTH, &textureWidth);
        // std::cout << textureWidth << ", " << healer_texture << std::endl;
        // bunny->draw();
        userChar->draw();

        glBindBufferRange(GL_UNIFORM_BUFFER, 2, objects_buffer, 2 * 256, sizeof(ObjectUBO));

        enemyChar->draw();
        break;
    case PLAY_LOCAL_PVP:
        //     renderer.localPvPRender(pvp_program);
        break;
    }
    // bunny->draw();
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
        renderer.aiPlayRender(width, height, &gameState, gear_texture);
        break;
    // case PLAY_LOCAL_PVP:
    //     // renderer.localPvPRender(pvp_program);
    //     break;
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
    // std::cout << x << " - x position" << std::endl;
    // if (x <) {
    // glm::vec3 pos = camera.get_eye_position();
    camera.on_mouse_move(x, y);
    // }
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