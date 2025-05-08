#include "../../include/Game.hpp"


Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "map4");
    user1 = User("myname");
}

void Game::draw_all(){
    gameMap.draw(window);
    user1.draw(window);
}

void Game:: runGame()
{
    Unit** user1_units = user1.unitDeck.getUnits();
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
            
                
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                bool* picks = user1.unitDeck.getIsPicked();
                for(int i = 0; i < MAX_UNITS; i++){
                    if(picks[i]){
                        //deploy the unit at the desired location
                        user1.deploy(user1_units[i], sf::Mouse::getPosition());
                    }
                }
            }
            
        }
        
        window->clear();
        draw_all();
        window->display();
    }
}