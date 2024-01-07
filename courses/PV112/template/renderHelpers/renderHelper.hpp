// TODO is this needed ?
#pragma once
#include "../gameHelpers/gameState.hpp"
// #ifndef GLM_ENABLE_EXPERIMENTAL
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/ext.hpp>
// #endif
#include <iostream>
#include "glad/glad.h"
#include "imgui.h"
#include "../colors.hpp"

class Renderer
{
private:
    ImGuiWindowFlags windowFlag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    ImGuiStyle windowStyle;
    ImVec4 mapRGBAToVectorColor(int red, int green, int blue, float alpha);
    colors cHelper = colors::colors();
    const char *gameName = "~HEROES OF DERILIA~";

public:
    Renderer();
    ~Renderer();
    void howToPlayRender(GLuint program);
    void aiPlayRender(GLuint program);
    void playMenuRender(GLuint program);
    void menuRender(int width, int height, gameState *state);
    void localPvPRender(GLuint program);
};