// ################################################################################
// Common Framework for Computer Graphics Courses at FI MUNI.
//
// Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
// All rights reserved.
// ################################################################################

#pragma once

#include "camera.h"
#include "cube.hpp"
#include "pv112_application.hpp"
#include "renderHelpers/renderHelper.hpp"
#include "sphere.hpp"
#include "teapot.hpp"

// ----------------------------------------------------------------------------
// UNIFORM STRUCTS
// ----------------------------------------------------------------------------
struct CameraUBO
{
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec4 position;
};

struct alignas(16) LightAttenuation
{
    float constant;
    float linear;
    float quadratic;
};

struct LightUBO
{
    glm::vec4 position;
    glm::vec4 ambient_color;
    glm::vec4 diffuse_color;
    glm::vec4 specular_color;
    LightAttenuation attenuation;
};

struct ConeLightUBO
{
    glm::vec4 position;
    glm::vec4 ambient_color;
    glm::vec4 diffuse_color;
    glm::vec4 specular_color;
    glm::vec4 direction;
    float angle;
    float padding1;
    float padding2;
    float padding3;
    LightAttenuation attenuation;
};

struct alignas(32) FogUBO
{
    glm::vec4 color;
    float density;
    float end;
};

struct alignas(256) ObjectUBO
{
    glm::mat4 model_matrix;  // [  0 -  64) bytes
    glm::vec4 ambient_color; // [ 64 -  80) bytes
    glm::vec4 diffuse_color; // [ 80 -  96) bytes

    // Contains shininess in .w element
    glm::vec4 specular_color; // [ 96 - 112) bytes
};

// Constants
const float clear_color[4] = {0.0, 0.0, 0.0, 1.0};
const float clear_depth[1] = {1.0};

class Application : public PV112Application
{

    // ----------------------------------------------------------------------------
    // Variables
    // ----------------------------------------------------------------------------
    std::filesystem::path images_path;
    std::filesystem::path objects_path;

    // Programs
    GLuint main_program;
    GLuint lights_program;
    bool initedPrograms = false;

    // List of geometries used in the project
    std::vector<std::shared_ptr<Geometry>> geometries;
    // Shared pointers are pointers that automatically count how many times they are used. When there are 0 pointers to the object pointed
    // by shared_ptrs, the object is automatically deallocated. Consequently, we gain 3 main properties:
    // 1. Objects are not unnecessarily copied
    // 2. We don't have to track pointers
    // 3. We don't have to deallocate these geometries
    std::shared_ptr<Geometry> sphere;
    std::shared_ptr<Geometry> bunny;
    std::shared_ptr<Geometry> userChar;
    std::shared_ptr<Geometry> enemyChar;
    std::shared_ptr<Geometry> ground;
    std::shared_ptr<Geometry> sky;
    std::shared_ptr<Geometry> deadTree;
    std::shared_ptr<Geometry> tree;

    // Default camera that rotates around center.
    Camera camera;

    // UBOs
    GLuint camera_buffer = 0;
    CameraUBO camera_ubo;

    GLuint light_buffer = 0;
    LightUBO light_ubo;

    GLuint objects_buffer = 0;
    std::vector<ObjectUBO> objects_ubos;

    GLuint fog_buffer = 0;
    FogUBO fog_ubo;

    // Lights
    std::vector<ConeLightUBO> coneLights;
    GLuint lights_buffer = 0;
    ConeLightUBO userCharLight;
    ConeLightUBO enemyCharLight;

    // Textures
    GLuint marble_texture = 0;
    GLuint gear_texture = 0;
    GLuint ground_texture = 0;
    GLuint sky_texture = 0;
    GLuint ogre_texture = 0;
    GLuint deadTree_texture = 0;
    GLuint tree_texture = 0;

    // Game Helper classes and variables
    gameState gameState = gameState::gameState();

    // user char
    glm::vec3 userCharPos;
    glm::mat4 charRotation;
    glm::mat4 charScale;
    ObjectUBO userCharM;
    std::vector<glm::vec3> userAnimatePos = {
        glm::vec3(-1.f, -0.1f, 7.5f),
        glm::vec3(-0.6f, -0.1f, 7.f),
        glm::vec3(-0.2f, -0.1f, 6.5f),
        glm::vec3(0.2f, -0.1f, 6.f),
        glm::vec3(0.6f, -0.1f, 5.5f),
        glm::vec3(1.f, -0.1f, 5.f)};

    // enemy char
    glm::vec3 enemyCharPos;
    glm::mat4 enemyCharRotation;
    glm::mat4 enemyCharScale;
    ObjectUBO enemyCharM;
    std::vector<glm::vec3> enemyAnimatePos = {
        glm::vec3(3.f, -0.1f, 2.5f),
        glm::vec3(2.6f, -0.1f, 3.0f),
        glm::vec3(2.2f, -0.1f, 3.5f),
        glm::vec3(1.8f, -0.1f, 4.f),
        glm::vec3(1.4f, -0.1f, 4.5f),
        glm::vec3(1.f, -0.1f, 5.f)};

    //
    glm::vec3 dirToEnemy;
    glm::vec3 dirToUser;
    glm::vec3 currentPosition;
    bool isAnimating = false;
    bool shouldAnimate = false;
    bool enemyAnimate = false;
    bool backwards = false;
    float animateTimeout = 100.f;
    float deltaMerge = 0.f;
    int posIndex = 0;
    int maxIndex = 5;

    // Renderer helper class
    Renderer renderer;
    SoundData soundData;

private:
    void initSound();
    void freeSound();

    // ----------------------------------------------------------------------------
    // Constructors & Destructors
    // ----------------------------------------------------------------------------
public:
    /**
     * Constructs a new @link Application with a custom width and height.
     *
     * @param 	initial_width 	The initial width of the window.
     * @param 	initial_height	The initial height of the window.
     * @param 	arguments	  	The command line arguments used to obtain the application directory.
     */
    Application(int initial_width, int initial_height, std::vector<std::string> arguments = {});

    /** Destroys the {@link Application} and releases the allocated resources. */
    ~Application() override;

    // ----------------------------------------------------------------------------
    // Methods
    // ----------------------------------------------------------------------------

    /** @copydoc PV112Application::compile_shaders */
    void compile_shaders() override;

    /** @copydoc PV112Application::delete_shaders */
    void delete_shaders() override;

    /** @copydoc PV112Application::update */
    /**
     * This method is invoked from within the infinite OpenGL loop. The purpose of this method is to update the
     * application specific data before rendering the content.
     *
     * @param 	delta	The elapsed time between this and the previous frame (in milliseconds).
     */
    void update(float delta) override;

    /** @copydoc PV112Application::render */
    void render() override;

    /** @copydoc PV112Application::render_ui */
    void render_ui() override;

    // ----------------------------------------------------------------------------
    // Input Events
    // ----------------------------------------------------------------------------

    /** @copydoc PV112Application::on_resize */
    void on_resize(int width, int height) override;

    /** @copydoc PV112Application::on_mouse_move */
    void on_mouse_move(double x, double y) override;

    /** @copydoc PV112Application::on_mouse_button */
    void on_mouse_button(int button, int action, int mods) override;

    /** @copydoc PV112Application::on_key_pressed */
    void on_key_pressed(int key, int scancode, int action, int mods) override;
};
