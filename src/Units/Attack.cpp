#include "../../include/Attack.hpp"
#include "../../include/Unit.hpp"
#include <iostream>

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
    float displacement_x = target->getFloatLoc().x - location.x;
    float displacement_y = target->getFloatLoc().y - location.y;

    float time_x = displacement_x/speed;
    float time_y = displacement_y/speed;
    attackSprite.move(sf::Vector2f(displacement_x/time_x, displacement_y/time_y));
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
        if (owner == unitlist[i]){
            continue;
        }
        if (collision_box.intersects(unitlist[i]->getSkin().getGlobalBounds())){
            isActive = false;
            unitlist[i]->takeDamage(*this);
            std:: cout << "HIT!!\n";
            return true;
        }
    }
    return false;
}

std:: string Attack::describe(){
    std:: string exist = "The attack is exist!\n";
    return exist;
}