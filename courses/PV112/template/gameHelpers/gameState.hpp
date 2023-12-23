#include <list>

enum gameStateE
{
    GAME_EXIT,
    GAME_MENU,
    PLAY_VS_AI,
    PLAY_LOCAL_PVP,
    HOW_TO_PLAY,
    PLAY_MENU
};

class gameState
{
private:
    std::list<gameStateE> previousStates = {};

public:
    gameStateE currentState;
    gameState()
    {
        currentState = GAME_MENU;
    };
    ~gameState()
    {
        previousStates.~list();
    }
    /**
     * Goes back to the previous state, if no states present exits the game.
     */
    void Back();
    /**
     * Exits the game.
     */
    void Exit();
    /**
     * Changes the state to GAME_MENU.
     */
    void GameMenu();
    /**
     * Changes the state to PLAY_VS_AI.
     */
    void PlayVsAI();
    /**
     * Changes the state to PLAY_LOCAL_PVP.
     */
    void PlayLocalPVP();
    /**
     * Changes the state to HOW_TO_PLAY.
     */
    void HowToPlay();
    /**
     * Changes the state to PLAY_MENU.
     */
    void PlayMenu();
};