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
    // initializers
    Entity();
    Entity(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst);

    //getters
    float getDamage();
    sf::Vector2f getLocation();
    float getSpeed();
    float getRadius_of_attack();
    int getCost();

    //setters
    void setDamage(float new_dmg);
    void setSpeed(float new_sp);
    void setLocation(sf::Vector2f *newloc);
    void setRadius_of_attack(float radius);
    void setCost(int new_c);

   
};

#endif