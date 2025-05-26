#include "../../include/CustomizeWindow.hpp"

CustomizeWindow::CustomizeWindow(){
    m_window = nullptr;
}

int CustomizeWindow::runWindow(){
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "CustomizeWindow");
    while(m_window->isOpen()){
        std:: cout << "Window is open for customization\n";
        sf::Event event;
        while(m_window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                m_window->close();
            }
        }
    }
    return 0;
}