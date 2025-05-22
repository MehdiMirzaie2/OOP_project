#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <SFML/Graphics.hpp>
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

class Drawable // abstract interface for all drawables
{
    public:
       virtual void draw(sf::RenderWindow* window) = 0;
};

#endif // DRAWABLE_HPP_