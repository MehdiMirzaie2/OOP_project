#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Window.hpp"
#include <SFML/Graphics.hpp>
const int menu_options = 3;


class MainMenu : public Window{

    private:
        sf::Sprite title;
        sf::Texture titleTexture;
        sf::Sprite menuBG;
        sf::Texture menuBGTexture;
        sf::Text* menuTexts;
        sf::Font font;

    public:
        MainMenu();
        void draw_all(sf::RenderWindow* window);
        int runWindow();
};


#endif // MAINMENU_HPP_