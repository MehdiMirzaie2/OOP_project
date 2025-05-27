#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <array>

const int menu_options = 3; // Number of menu options displayed

class MainMenu : public Window
{
private:
    sf::Sprite m_title; // Sprite for the title image
    sf::Texture m_titleTexture; // Texture for the title sprite
    sf::Sprite m_menuBG; // Sprite for the menu background
    sf::Texture m_menuBGTexture; // Texture for the background sprite
    std::array<sf::Text, menu_options> m_menuTexts; // Text objects for menu options
    sf::Font m_font; // Font used for menu texts

public:
    MainMenu(); // Constructor to load assets and initialize the menu
    void draw_all(sf::RenderWindow *window); // Draws the entire menu to the window
    int runWindow(); // Runs the main menu loop and returns the selected option
};

#endif // MAINMENU_HPP_
