#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

const int WINDOW_WIDTH = 1160;  // Default window width
const int WINDOW_HEIGHT = 540;  // Default window height

class Window
{
protected:
    std::unique_ptr<sf::RenderWindow> m_window; // Pointer to SFML render window

public:
    virtual int runWindow() = 0; // Pure virtual function to run the window loop
};

#endif // WINDOW_HPP_
