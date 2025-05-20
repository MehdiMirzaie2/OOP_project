#ifndef UNITS_HEADER_GAME_HPP_
#define UNITS_HEADER_GAME_HPP_

#include "User.hpp"
#include "BattleWindow.hpp"
#include "CustomizeWindow.hpp"
#include "MainMenu.hpp"
#include "GameDataManager.hpp"

class Game{

    private:
        BattleWindow battleWindow;
        CustomizeWindow customizeWindow;
        MainMenu menuWindow;
        GameDataManager userData;
       
    public:
        Game();
        void runGame();
        
        
};


#endif // UNITS_HEADER_GAME_HPP_