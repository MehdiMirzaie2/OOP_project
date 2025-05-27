#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
class Drawable // abstract interface for all drawables
{
    protected:
        sf::Texture m_unitTextureIdle; // Texture when idle
        sf::Texture m_unitTextureAttacking; // Texture when attacking
        sf::Texture m_deadTexture; // Texture when dead

        std::string m_projectileTextureName; // Projectile texture identifier
        std::string m_unitTextureIdleName; // Idle texture identifier
        std::string m_unitTextureAttackingName; // Attacking texture identifier

    public:
	    Drawable();
        Drawable(std::string, std::string, std::string);
        virtual void draw(sf::RenderWindow* window) = 0;
        virtual ~Drawable() = default; 

        std::string getProjectileTextureName(); 
        std::string getIdleTextureName();
        std::string getAttackingTextureName();
};

#endif // DRAWABLE_HPP_
