#include "../../include/CustomizeWindow.hpp"

CustomizeWindow::CustomizeWindow(){
    window = nullptr;
}

int CustomizeWindow::runWindow(){
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "CustomizeWindow");
    while(window->isOpen()){
        std:: cout << "Window is open for customization\n";
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
        }
    }
    return 0;
}