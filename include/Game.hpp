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
    std::string statsFile;
    User m_user1; 
    User m_user2;

public:
    Game();
    void runGame();
    void registerWinner(int winner);
};

#endif // UNITS_HEADER_GAME_HPP_