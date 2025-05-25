#include "../../include/MainMenu.hpp"
#include <iostream>


int MainMenu::runWindow()
{
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Main Menu");
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
        draw_all(window.get());
        window->display();
    }
    return 0;
}

void MainMenu::draw_all(sf::RenderWindow* window){
    window->draw(menuBG);
    for(int i = 0; i < menu_options; i++){
        window->draw(menuTexts[i]);
    }
    window->draw(title);
}

MainMenu::MainMenu()
{
    window = nullptr;
    if(!font.loadFromFile("./src/Fonts/Quicksand-Bold.ttf")){
        std::cout << "Unable to load font!\n";
    }
    if (!menuBGTexture.loadFromFile("src/Textures/main-menu-bg.png")){
        std::cout << "Unable to load Main menu Texture\n";
    }
    menuBG.setOrigin(menuBGTexture.getSize().x/2.f, menuBGTexture.getSize().y/2.f);
    menuBG.setTexture(menuBGTexture);
    menuBG.setPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    menuTexts[0].setString("Play");
    menuTexts[1].setString("Units");
    menuTexts[2].setString("Exit");
    sf::Vector2f start = sf::Vector2f(WINDOW_WIDTH/2.f - 30, WINDOW_HEIGHT/2.f); // Starting position for first option - play
    sf::Vector2f padding_y(0, 40); // Padding between successive options , eg between play and options

    for(int i = 0; i < menu_options; i++){
        menuTexts[i].setFont(font);
        sf::FloatRect textBounds = menuTexts[i].getLocalBounds();
        float centerX = textBounds.left + textBounds.width / 2.0f;
        float centerY = textBounds.top + textBounds.height / 2.0f;
        menuTexts[i].setOrigin(centerX, centerY);
        
        menuTexts[i].setFillColor(sf::Color::White);
        menuTexts[i].setOutlineColor(sf::Color(220, 220, 220, 1));
        menuTexts[i].setPosition(start + padding_y);
        start = menuTexts[i].getPosition();
    }

    // Set the title of the game:
   if(!titleTexture.loadFromFile("src/Textures/title.png")){
        std::cout << "Unable to load title texture\n";
   }
   title.setOrigin(titleTexture.getSize().x/2.f, titleTexture.getSize().y/2.f);
   title.setTexture(titleTexture);
   title.setPosition(WINDOW_WIDTH/2.f, 110);
   title.setScale(0.8, 0.8);
}