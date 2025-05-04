#include "../header/Entity.hpp"

Entity::Entity(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst)
{
    location = std::make_unique<sf::Vector2f>(loc_x, loc_y);
    damage = dmg;
    speed = spd;
    radius_of_attack = radius_atk;
    cost = cst;
}

void Entity::setLocation(sf::Vector2f *newloc) { location.reset(newloc); };
sf::Vector2f Entity::getLocation() { return *location; };

float Entity::getDamage() { return damage; };
void Entity::setDamage(float new_dmg) { damage = new_dmg; };

float Entity::getSpeed() { return speed; };
void Entity::setSpeed(float new_sp) { speed = new_sp; };

float Entity::getRadius_of_attack() { return radius_of_attack; };
void Entity::setRadius_of_attack(float radius) { radius_of_attack = radius; };

int Entity::getCost() { return cost; };
void Entity::setCost(int new_c) { cost = new_c; };
