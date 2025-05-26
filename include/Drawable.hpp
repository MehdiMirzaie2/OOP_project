#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Drawable // abstract interface for all drawables
{
protected:
    sf::Texture m_unitTextureIdle;
    sf::Texture m_unitTextureAttacking;
    sf::Texture m_deadTexture;
    sf::Texture m_projectileTexture;

    std::string m_projectileTextureName;
    std::string m_unitTextureIdleName;
    std::string m_unitTextureAttackingName;

public:
    Drawable(std::string, std::string, std::string);

    virtual void draw(sf::RenderWindow *window) = 0;
};

#endif // DRAWABLE_HPP_