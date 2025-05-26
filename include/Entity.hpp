#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Drawable.hpp"
#include <memory>

// Viable entities include units, attacks, spells
// HP is invalid for attacks/spells so didn't include to make a more generic abstract class

class Entity : public Drawable
{
protected:
    // hp bar if possible
    float m_damage; // The viable entities all have these variables
    sf::Sprite m_skin;
    float m_speed;
    float m_radius_of_attack;
    int m_cost;
    bool m_isActive;

public:
    // initializers
    Entity();
    Entity(float dmg, sf::Vector2f location, float spd, float radius_atk, int cst);

    // getters
    float getDamage();
    sf::Vector2f getLocation();
    float getSpeed();
    float getRadius_of_attack();
    int getCost();
    bool getisActive();

    // setters
    void setDamage(float new_dmg);
    void setSpeed(float new_sp);
    void setLocation(sf::Vector2f newloc);
    void setRadius_of_attack(float radius);
    void setCost(int new_c);
    void setisActive(bool active);

    //util
    virtual void draw(sf::RenderWindow *window) = 0;
};

#endif