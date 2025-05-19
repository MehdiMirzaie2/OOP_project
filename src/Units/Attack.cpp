#include "../../include/Attack.hpp"
#include <iostream>

Attack::Attack()
{
    if (!texture.loadFromFile("src/Textures/vecteezy_archer-arrow-icon-png_21126813.png")){
        std:: cout << "Unable to load texture\n";
    }
    isActive = false;
    speed = 2;
    sprite.setTexture(texture);
    sprite.setScale(0.005f, 0.005f);
}

void Attack::shoot(sf::Vector2f shooting_location)
{
    sprite.setPosition(shooting_location);
    isActive = true;
}

void Attack::move()
{
    sprite.move(sf::Vector2f(speed, 0));
}

bool Attack::getisActive(){return isActive;};

void Attack::updateLocation(sf::Vector2f new_loc)
{
    sprite.setPosition(new_loc);
}

void Attack::draw(sf::RenderWindow* window)
{  
    window->draw(sprite);
}