#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>

class Window
{
    protected:
        sf::RenderWindow* window;

    public:
        virtual void runWindow() = 0;

};

#endif // WINDOW_HPP_