#include "../../include/MainMenu.hpp"
#include <iostream>

int MainMenu::runWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(menu_display_width, menu_display_height), "Main Menu");
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                for (int i = 0; i < menu_options; i++){
                    if (menuTexts[i].getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))){
                        std:: string name = menuTexts[i].getString();
                        std::cout << "CLICKED ON " << name << std:: endl;
                        window->close();
                        return i+1;
                    }
                }
            }
        }
        window->clear();
        draw_all(window);
        window->display();
    }
    return 0;
}

void MainMenu::draw_all(sf::RenderWindow* window){
    for(int i = 0; i < menu_options; i++){
        window->draw(menuTexts[i]);
    }
}

MainMenu::MainMenu()
{
    window = nullptr;
    if(!font.loadFromFile("./src/Fonts/Quicksand-Bold.ttf")){
        std::cout << "Unable to load font!\n";
    }
    menuTexts = new sf::Text[menu_options];
    menuTexts[0].setString("Play");
    menuTexts[1].setString("Units");
    menuTexts[2].setString("Exit");
    sf::Vector2f start = sf::Vector2f(menu_display_width/2.f, menu_display_height/2.f - 240); // Starting position for first option - play
    sf::Vector2f padding_y(0, 40); // Padding between successive options , eg between play and options

    for(int i = 0; i < menu_options; i++){
        sf::FloatRect textBounds = menuTexts[i].getLocalBounds();
        float centerX = textBounds.left + textBounds.width / 2.0f;
        float centerY = textBounds.top + textBounds.height / 2.0f;
        menuTexts[i].setOrigin(centerX, centerY);
        menuTexts[i].setFont(font);
        menuTexts[i].setFillColor(sf::Color::White);
        menuTexts[i].setOutlineColor(sf::Color(220, 220, 220, 1));
        menuTexts[i].setPosition(start + padding_y);
        start = menuTexts[i].getPosition();
    }

    
}