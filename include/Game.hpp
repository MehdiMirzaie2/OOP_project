#ifndef UNITS_HEADER_GAME_HPP_
#define UNITS_HEADER_GAME_HPP_

#include "User.hpp"
#include "BattleWindow.hpp"
#include "CustomizeWindow.hpp"
#include "MainMenu.hpp"

class Game
{
private:
    BattleWindow m_battleWindow;    // Handles the battle gameplay screen
    CustomizeWindow m_customizeWindow; // Handles customization UI
    MainMenu m_menuWindow;          // Handles main menu UI

public:
    Game();          // Constructor to initialize the game and its windows
    void runGame();  // Main game loop controlling flow between windows
};

#endif // UNITS_HEADER_GAME_HPP_
