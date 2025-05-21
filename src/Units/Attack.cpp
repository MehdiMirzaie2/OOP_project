#include "../../include/Attack.hpp"
#include "../../include/Unit.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

Attack::Attack(Unit* owner, std:: string attackTextureName, Unit* target)
{
    if (!attackTexture.loadFromFile("src/Textures/" + attackTextureName))
    {
        std::cout << "Unable to load attack texture: src/Textures/" << attackTextureName << std::endl;
        
    }
    else{
        std::cout << "Loaded attack texture : src/Textures/" << attackTextureName << std:: endl;
    }
    isActive = false;
    damage = 20;
    speed = 0.5;
    attackSprite.setOrigin(attackTexture.getSize().x/2.f, attackTexture.getSize().y/2.f);
    attackSprite.setTexture(attackTexture);
    attackSprite.setScale(0.2f, 0.2f);
    this->owner = owner;
    this->target = target;
}

void Attack::shoot(sf::Vector2f shooting_location)
{
    attackSprite.setPosition(shooting_location);
    isActive = true;
}

void Attack::move()
{
    sf::Vector2f location = attackSprite.getPosition();
    float displacement_x = target->getLocation().x - location.x;
    float displacement_y = target->getLocation().y - location.y;

    // To calculate the unit vector for direction, as the above vector is not a unit vector, we divide by distance

    float distance = std::sqrt((displacement_x*displacement_x) + (displacement_y*displacement_y));
    float normalized_displacement_x = displacement_x/distance;
    float normalized_displacement_y = displacement_y/distance;

    
    attackSprite.move(sf::Vector2f(normalized_displacement_x*speed, normalized_displacement_y*speed));
}

bool Attack::getisActive(){return isActive;};

int Attack::getDamage(){return damage;};

void Attack::updateLocation(sf::Vector2f new_loc)
{
    attackSprite.setPosition(new_loc);
}

void Attack::draw(sf::RenderWindow* window)
{  
    window->draw(attackSprite);
}

void Attack::update()
{
    if (getisActive()){
        move();
    }
}

bool Attack::isHit(std::vector<Unit*> unitlist)
{
    sf::FloatRect collision_box = attackSprite.getGlobalBounds();
    for(long unsigned int i = 0; i < unitlist.size(); i++){
        if (owner == unitlist[i] || unitlist[i]->getisDead()){
            continue;
        }
        if (collision_box.intersects(unitlist[i]->getSkin().getGlobalBounds())){
            isActive = false;
            if(unitlist[i]->getisActive()){
                unitlist[i]->takeDamage(*this);
                std:: cout << "HIT!!\n";
                Unit::active_attacks.erase(std::find(Unit::active_attacks.begin(), Unit::active_attacks.end(), this));
                return true;
            }
        }
    }
    return false;
}

std:: string Attack::describe(){
    std:: string exist = "The attack is exist!\n";
    return exist;
}