#include "../../include/MainMenu.hpp"
#include <iostream>


int MainMenu::runWindow()
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Main Menu");
    while(m_window->isOpen()){
        sf::Event event;
        while(m_window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                m_window->close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                for (int i = 0; i < menu_options; i++){
                    if (m_menuTexts[i].getGlobalBounds().contains(m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)))){
                        std:: string name = m_menuTexts[i].getString();
                        std::cout << "CLICKED ON " << name << std:: endl;
                        m_window->close();
                        return i+1;
                    }
                }
            }
        }
        m_window->clear();
        draw_all(m_window.get());
        m_window->display();
    }
    return 0;
}

void MainMenu::draw_all(sf::RenderWindow* window){
    window->draw(m_menuBG);
    for(int i = 0; i < menu_options; i++){
        window->draw(m_menuTexts[i]);
    }
    window->draw(m_title);
}

MainMenu::MainMenu()
{
    m_window = nullptr;
    if(!m_font.loadFromFile("./src/Fonts/Quicksand-Bold.ttf")){
        std::cout << "Unable to load font!\n";
    }
    if (!m_menuBGTexture.loadFromFile("src/Textures/main-menu-bg.png")){
        std::cout << "Unable to load Main menu Texture\n";
    }
    m_menuBG.setOrigin(m_menuBGTexture.getSize().x/2.f, m_menuBGTexture.getSize().y/2.f);
    m_menuBG.setTexture(m_menuBGTexture);
    m_menuBG.setPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    m_menuTexts[0].setString("Play");
    m_menuTexts[1].setString("Stats");
    m_menuTexts[2].setString("Exit");
    sf::Vector2f start = sf::Vector2f(WINDOW_WIDTH/2.f - 30, WINDOW_HEIGHT/2.f); // Starting position for first option - play
    sf::Vector2f padding_y(0, 40); // Padding between successive options , eg between play and options

    for(int i = 0; i < menu_options; i++){
        m_menuTexts[i].setFont(m_font);
        sf::FloatRect textBounds =m_menuTexts[i].getLocalBounds();
        float centerX = textBounds.left + textBounds.width / 2.0f;
        float centerY = textBounds.top + textBounds.height / 2.0f;
        m_menuTexts[i].setOrigin(centerX, centerY);
        
        m_menuTexts[i].setFillColor(sf::Color::White);
        m_menuTexts[i].setOutlineColor(sf::Color(220, 220, 220, 1));
        m_menuTexts[i].setPosition(start + padding_y);
        start = m_menuTexts[i].getPosition();
    }

    // Set the title of the game:
   if(!m_titleTexture.loadFromFile("src/Textures/title.png")){
        std::cout << "Unable to load title texture\n";
   }
   m_title.setOrigin(m_titleTexture.getSize().x/2.f, m_titleTexture.getSize().y/2.f);
   m_title.setTexture(m_titleTexture);
   m_title.setPosition(WINDOW_WIDTH/2.f, 110);
   m_title.setScale(0.8, 0.8);
}