#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <SFML/Graphics.hpp>

class Drawable // abstract interface for all drawables
{
    public:
       virtual void draw(sf::RenderWindow* window) = 0;
       virtual ~Drawable() = default; 

};

#endif // DRAWABLE_HPP_