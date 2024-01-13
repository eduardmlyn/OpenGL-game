#include "gameState.hpp"

void gameState::Back()
{
    if (previousStates.empty())
    {
        this->Exit();
        return;
    }
    currentState = previousStates.back();
    previousStates.pop_back();
};

void gameState::Exit()
{
    previousStates.clear();
    currentState = GAME_EXIT;
}

void gameState::GameMenu()
{
    previousStates.push_back(currentState);
    currentState = GAME_MENU;
}

void gameState::PlayVsAI()
{
    previousStates.push_back(currentState);
    currentState = PLAY_VS_AI;
}

void gameState::PlayLocalPVP()
{
    previousStates.push_back(currentState);
    currentState = PLAY_LOCAL_PVP;
}

void gameState::HowToPlay()
{
    previousStates.push_back(currentState);
    currentState = HOW_TO_PLAY;
}

void gameState::PlayMenu()
{
    previousStates.push_back(currentState);
    currentState = PLAY_MENU;
}

void gameState::PrintStateList()
{
    for (const auto &element : previousStates)
    {
        std::cout << element << ", ";
    }
}