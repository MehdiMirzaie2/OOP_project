#ifndef UNITS_HEADER_GAME_HPP_
#define UNITS_HEADER_GAME_HPP_

#include "User.hpp"
#include "map.hpp"
#include "SFML/Graphics.hpp"


class Game{
    private:
        sf::RenderWindow* window;
        Map gameMap;
        
    public:
        Game();
        void draw_all();
        void runGame();
        
};


#endif // UNITS_HEADER_GAME_HPP_