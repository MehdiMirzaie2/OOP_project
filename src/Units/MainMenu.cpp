#include "../../include/MainMenu.hpp"
#include <iostream>

MainMenu::runWindow()
{
    while(window->isOpen()){
        // user controls up down to navigate menu
    }
}

MainMenu::MainMenu()
{
    if(!sf::Font::loadFromFile("OOP_project/src/Fonts/Quicksand-Bold.ttf")){
        std::cout << "Unable to load font!\n";
    }
    menuTexts = new sf::Text[menu_options];
    
    sf::Vector2f start = sf::Vector2f(menu_display_width/2.f, menu_display_height/2.f - 240);
    sf::Vector2f padding_y(0, 40);

    for(int i = 0; i < menu_options; i++){
        sf::FloatRect textBounds = myText.getLocalBounds();
        float centerX = textBounds.left + textBounds.width / 2.0f;
        float centerY = textBounds.top + textBounds.height / 2.0f;
        menuTexts[i].setOrigin(centerX, centerY);
        menuTexts[i].setFont(font);
        menuTexts[i].setFillColor(sf::Color::White);
        menuTexts[i].setOutlineColor(sf::Color(220, 220, 220, 1));
        menuTexts[i].setPosition(start + padding_y);
    }

    menuTexts[0].setString("Play");
    menuTexts[1].setString("Units");
    menuTexts[2].setString("Exit");


}