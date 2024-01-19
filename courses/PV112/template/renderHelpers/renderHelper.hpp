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
    // TODO: fix when scrolling main window and child window stays on same coordinates
    ImGuiWindowFlags childWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysVerticalScrollbar;
    ImGuiWindowFlags playMenuFlags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNavInputs;
    ImGuiStyle windowStyle;
    ImVec4 mapRGBAToVectorColor(int red, int green, int blue, float alpha);
    colors cHelper = colors::colors();
    const char *gameName = "HEROES OF DERILIA";
    const char *howToPlayS = "How to play:";
    const char *howToPlayDesc = "The game is a turn based game, with five characters of "
                                "different classes. You can either play versus AI or play 1 vs 1 against your friend on the same pc. "
                                "The goal of the game is to kill all enemy units before they kill your units. When one of "
                                "the teams has 0 units the game concludes. The classes and heroes in each team are "
                                "identical, and these are:\n\n"
                                "Elysian, the Arcanist(Mage)\n"
                                "  Basic attack:\n"
                                "\tdeals damage, gains 8 mana.\n"
                                "--First special ability--\n"
                                "Fireball (cooldown of 4):\n"
                                "cost - 45 mana\n"
                                "\tdeals ability damage to target enemy, applies defense down.\n"
                                "--Second special ability--\n"
                                "Aetheric purge (cooldown of 6):\n"
                                "cost - 60 mana\n"
                                "\tdeals ability damage to all enemies, dispells all buffs on target enemy.\n\n"
                                "Luna, the Swiftshot(Marksman)\n"
                                "  Basic attack:\n"
                                "\tdeals damage, gains 5 mana.\n"
                                "--First special ability--\n"
                                "Marksman's Fury (cooldown of 3):\n"
                                "cost - 20 mana\n"
                                "\tdeals damage three times.\n"
                                "--Second special ability--\n"
                                "Agility (cooldown of 2):\n"
                                "cost - 15 mana\n"
                                "\tgain speed up, attack damage up, accuracy up.\n\n"
                                "Faelan, the Lightweaver(Healer)\n"
                                "  Basic attack:\n"
                                "\tdeals damage, gains 5 mana.\n"
                                "--First special ability--\n"
                                "Holy guardian (cooldown of 4):\n"
                                "cost - 60 mana\n"
                                "\theals all allies, dispells all debuffs on allies.\n"
                                "--Second special ability--\n"
                                "Divine support (cooldown of 3):\n"
                                "cost - 50 mana\n"
                                "\theals target ally and gives him speed up, defense up, accuracy up.\n\n"
                                "Viktor, the Steelwall(Tank)\n"
                                "  Basic attack:\n"
                                "\tdeals damage, gains 5 mana and defense up.\n"
                                "--First special ability--\n"
                                "Battle cry (cooldown of 4):\n"
                                "cost - 25 mana\n"
                                "\theals self, gains defense up, gives ALL(self included) alies attack, ability damage up, accuracy up.\n"
                                "--Second special ability--\n"
                                "Charge forward (cooldown of 4):\n"
                                "cost - 15 mana\n"
                                "\tgain taunt, defense up, deal damage to target enemy, and inflict the enemy with defense down and accuracy down.\n\n"
                                "Ryuji, the Shadowstrike(Assassin)\n"
                                "  Basic attack:\n"
                                "\tdeals damage, if the target is below 50%% health deals extra damage, gains 5 mana.\n"
                                "--First special ability--\n"
                                "Silent strike (cooldown of 5, starts on cooldown):\n"
                                "cost - 50 mana\n"
                                "\tdeal damage, instantly kill enemy if below 25%% health.\n"
                                "--Second special ability--\n"
                                "Assassin's remark (cooldown of 3):\n"
                                "cost 25 mana\n"
                                "\tgain speed up, accuracy up, critical chance up and inflict accuracy down, defense down, attack and ability damage down to target enemy.";

public:
    Renderer();
    ~Renderer();
    void howToPlayRender(int width, int height, gameState *state);
    void aiPlayRender(int width, int height, gameState *state, GLuint gearTexture);
    void playMenuRender(GLuint program);
    void menuRender(int width, int height, gameState *state);
    void localPvPRender(GLuint program);
};