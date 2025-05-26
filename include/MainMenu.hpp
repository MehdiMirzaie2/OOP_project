#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <array>
const int menu_options = 3;

class MainMenu : public Window
{
private:
    sf::Sprite m_title;
    sf::Texture m_titleTexture;
    sf::Sprite m_menuBG;
    sf::Texture m_menuBGTexture;
    std::array<sf::Text, menu_options> m_menuTexts;
    sf::Font m_font;

public:
    MainMenu();
    void draw_all(sf::RenderWindow *window);
    int runWindow();
};

#endif // MAINMENU_HPP_