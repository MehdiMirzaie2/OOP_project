#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

const int WINDOW_WIDTH = 1160;
const int WINDOW_HEIGHT = 540;

class Window
{
protected:
    std::unique_ptr<sf::RenderWindow> window;

public:
    virtual int runWindow() = 0;
};

#endif // WINDOW_HPP_