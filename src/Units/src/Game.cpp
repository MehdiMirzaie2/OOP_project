#include "../header/Game.hpp"

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "map4");
}

void Game::draw_all(){
    gameMap.drawMap(window);
}

void Game:: runGame()
{
    
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
        }
        
        window->clear();

       
        draw_all();

        window->display();
    }
}