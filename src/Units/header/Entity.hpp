#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SFML/Graphics.hpp"
#include <memory>

// Viable entities include units, attacks, spells
// HP is invalid for attacks/spells so didn't include to make a more generic abstract class

class Entity
{

protected:
    float damage; // The viable entities all have these variables
    std::unique_ptr<sf::Vector2f> location;
    float speed;
    float radius_of_attack;
    int cost;

public:
    Entity();
    Entity(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst);

    float getDamage();
    void setDamage(float new_dmg);

    float getSpeed();
    void setSpeed(float new_sp);

    sf::Vector2f getLocation();
    void setLocation(sf::Vector2f *newloc);

    float getRadius_of_attack();
    void setRadius_of_attack(float radius);

    int getCost();
    void setCost(int new_c);
};

#endif