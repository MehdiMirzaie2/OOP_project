#include "../../include/Attack.hpp"
#include "../../include/Unit.hpp"
#include <iostream>

Attack::Attack()
{
    if (!texture.loadFromFile("src/Textures/vecteezy_archer-arrow-icon-png_21126813.png")){
        std:: cout << "Unable to load texture\n";
    }
    isActive = false;
    damage = 20;
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

int Attack::getDamage(){return damage;};

void Attack::updateLocation(sf::Vector2f new_loc)
{
    sprite.setPosition(new_loc);
}

void Attack::draw(sf::RenderWindow* window)
{  
    window->draw(sprite);
}

bool Attack::isHit(std::vector<Unit*> unitlist)
{
    sf::FloatRect collision_box = sprite.getGlobalBounds();
    for(long unsigned int i = 0; i < unitlist.size(); i++){
        if (collision_box.contains(unitlist[i]->getFloatLoc())){
            isActive = false;
            unitlist[i]->takeDamage(*this);
            std:: cout << "HIT!!\n";
            return true;
        }
    }
    return false;
}