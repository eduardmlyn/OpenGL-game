#pragma once
#include "../gameHelpers/gameState.hpp"
#include "../gameHelpers/characterHelper.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "glad/glad.h"
#include "imgui.h"
#include "../colors.hpp"

class Renderer
{
private:
    ImGuiWindowFlags windowFlag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    // TODO: fix when scrolling main window and child window stays on same coordinates
    ImGuiWindowFlags childWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysVerticalScrollbar;
    ImGuiWindowFlags toggleMenuFlags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNavInputs;
    ImGuiWindowFlags playMenuFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    ImGuiWindowFlags characterDataFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing;
    ImGuiStyle windowStyle;
    ImVec4 mapRGBAToVectorColor(int red, int green, int blue, float alpha);
    colors cHelper = colors::colors();
    std::filesystem::path lecture_folder_path;
    CharacterAction charActionHelper;
    const char *gameName = "HERO OF DERILIA";
    const char *howToPlayS = "How to play:";
    const char *howToPlayDesc = "The game is a turn based game. "
                                "The goal of the game is to kill the enemy unit before they kill your unit. When one of "
                                "the units have 0 or less health the game concludes. "
                                "There are 3 abilities you can use. \n\n"
                                "Basic attack- deals 15 damage\n"
                                "Special attack- deals 25 damage\n"
                                "Defense- gain 30 armor.\n"
                                "Basic and Special attack can miss and deal critical damage."
                                "The critical damage deals 20%% more damage.";

public:
    Renderer(std::filesystem::path lecture_folder_path);
    Renderer();
    ~Renderer();
    void howToPlayRender(int width, int height, gameState *state);
    void aiPlayRender(int width, int height, gameState *state, GLuint gearTexture, bool inAnimation, bool *animateBody, bool *enemyAnimate);
    void playMenuRender(int width, int height, gameState *state);
    void menuRender(int width, int height, gameState *state);
    void localPvPRender(GLuint program);
    bool aiMove();
};