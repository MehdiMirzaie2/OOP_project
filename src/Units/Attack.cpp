#include "../../include/Attack.hpp"
#include "../../include/Unit.hpp"
#include <iostream>

Attack::Attack(std:: string attackTextureName)
{
    if (!attackTexture.loadFromFile("src/Textures/" + attackTextureName))
    {
        std:: cout << "Unable to load attack texture\n";
    }

    isActive = false;
    damage = 20;
    speed = 2;
    attackSprite.setOrigin(attackTexture.getSize().x/2.f, attackTexture.getSize().y/2.f);
    attackSprite.setTexture(attackTexture);
    attackSprite.setScale(0.2f, 0.2f);
    owner = nullptr;
}

Attack::Attack(Unit* owner, std:: string attackTextureName)
{
    if (!attackTexture.loadFromFile("src/Textures/" + attackTextureName))
    {
        std:: cout << "Unable to load attack texture\n";
    }
    isActive = false;
    damage = 20;
    speed = 2;
    attackSprite.setTexture(attackTexture);
    attackSprite.setScale(0.005f, 0.005f);
    this->owner = owner;
}

void Attack::shoot(sf::Vector2f shooting_location)
{
    attackSprite.setPosition(shooting_location);
    isActive = true;
}

void Attack::move()
{
    attackSprite.move(sf::Vector2f(speed, 0));
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