#ifndef UNITS_HEADER_GAME_HPP_
#define UNITS_HEADER_GAME_HPP_

#include "Window.hpp"
#include "User.hpp"
#include "map.hpp"
#include "Director.hpp"
#include "BattleWindow.hpp"
#include "GameDataManger.hpp"

class Game{

    private:
        Window* BattleWindow;
        Window* CustomizeWindow;
        Window* MenuWindow;
        GameDataManager userData;
       
    public:
        Game();
        void runGame();
        
        
};


#endif // UNITS_HEADER_GAME_HPP_