#ifndef UNITS_HEADER_GAME_HPP_
#define UNITS_HEADER_GAME_HPP_

#include "Window.hpp"
#include "User.hpp"
#include "map.hpp"

//Window that runs after you hit "play" on the menu

class Game : public Window{

    private:
        Map gameMap;
        User user1;
        
    public:
        Game();
        void draw_all();
        void runWindow();
        
};


#endif // UNITS_HEADER_GAME_HPP_