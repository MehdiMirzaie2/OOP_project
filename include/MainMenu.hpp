#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Window.hpp"
#include <SFML/Graphics.hpp>
const int menu_options = 3;
const int menu_display_height = 480;
const int menu_display_width = 620;

class MainMenu : public Window{

    private:
        sf::Text* menuTexts;
        sf::Font font;

    public:
        MainMenu();
        int runWindow();
};


#endif // MAINMENU_HPP_