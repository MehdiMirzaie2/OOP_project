#ifndef UNITS_HEADER_GAME_HPP_
#define UNITS_HEADER_GAME_HPP_

#include "User.hpp"
#include "BattleWindow.hpp"
#include "CustomizeWindow.hpp"
#include "MainMenu.hpp"

class Game
{
private:
    BattleWindow m_battleWindow;
    CustomizeWindow m_customizeWindow;
    MainMenu m_menuWindow;

public:
    Game();
    void runGame();
};

#endif // UNITS_HEADER_GAME_HPP_