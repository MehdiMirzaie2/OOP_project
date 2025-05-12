#include "../../include/BattleWindow.hpp"

void BattleWindow:: runWindow()
{
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
            
            // unit spawn logic, keep disabled until completed by me.
            // demo function to check spawning, otherwise director wouldn't be in the battleWindow
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
               Unit* myunit = director.buildRanger();
               user1.deploy(myunit, sf::Mouse::getPosition(), window);
            }
            
        }
        
        window->clear();
        draw_all();
        window->display();
    }
}

void Game::draw_all(){
    gameMap.draw(window);
    user1.draw(window);
}

