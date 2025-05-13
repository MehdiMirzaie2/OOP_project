#include "../../include/BattleWindow.hpp"

BattleWindow::BattleWindow(){
    window = nullptr;
}

int BattleWindow:: runWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "BattleWindow");
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
            
            // unit spawn logic, keep disabled until completed by me.
            // demo function to check spawning, otherwise director wouldn't be in the battleWindow
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
               Unit* myunit = director.buildRanger(" default (doesnt matter because the rangerBuilder does nothing with the setCustomization)");
               user1.deploy(myunit, sf::Mouse::getPosition(*window), window);
            }
            
        }
        
        window->clear();
        draw_all(window);
        window->display();
    }
    return 0;
}

void BattleWindow::draw_all(sf::RenderWindow* window){
    gameMap.draw(window);
    user1.draw(window);
}

