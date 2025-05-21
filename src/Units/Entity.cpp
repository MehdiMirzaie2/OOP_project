#include "../../include/Entity.hpp"

Entity::Entity(){}; // does nothing atm because I dont know what to put as the default values yet.

Entity::Entity(float dmg, sf::Vector2f location ,float spd, float radius_atk, int cst)
{
    damage = dmg;
    skin.setPosition(location);
    speed = spd;
    radius_of_attack = radius_atk;
    isActive = false;
    cost = cst;
}

void Entity::setisActive(bool active){isActive = active;};
bool Entity::getisActive(){return isActive;};

sf::Vector2f Entity::getLocation() { return skin.getPosition();};
void Entity::setLocation(sf::Vector2f new_loc){ skin.setPosition(new_loc);};

float Entity::getDamage() { return damage; };
void Entity::setDamage(float new_dmg) { damage = new_dmg; };

float Entity::getSpeed() { return speed; };
void Entity::setSpeed(float new_sp) { speed = new_sp; };

float Entity::getRadius_of_attack() { return radius_of_attack; };
void Entity::setRadius_of_attack(float radius) { radius_of_attack = radius; };

int Entity::getCost() { return cost; };
void Entity::setCost(int new_c) { cost = new_c; };
