#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Drawable.hpp"
#include <memory>

// Viable entities include units, attacks, spells
// HP is invalid for attacks/spells so didn't include to make a more generic abstract class

class Entity : public Drawable
{
protected:
    float m_damage; // Damage dealt by the entity
    sf::Sprite m_skin; // Visual representation of the entity
    float m_speed; // Movement speed of the entity
    float m_radius_of_attack; // Attack range
    int m_cost; // Elixir cost to deploy
    bool m_isActive; // Whether the entity is currently active

public:
    // Constructors
    Entity(); // Default constructor
    Entity(std::string a, std::string, std::string, float dmg, sf::Vector2f location, float spd, float radius_atk, int cst); // Initialize entity with key attributes

    // Getters
    float getDamage(); // Returns the entity's damage
    sf::Vector2f getLocation(); // Returns the entity's current position
    float getSpeed(); // Returns the entity's speed
    float getRadius_of_attack(); // Returns the attack radius
    int getCost(); // Returns the Elixir cost
    bool getisActive(); // Returns whether the entity is active

    // Setters
    void setDamage(float new_dmg); // Sets a new damage value
    void setSpeed(float new_sp); // Sets a new speed value
    void setLocation(sf::Vector2f newloc); // Updates the entity's location
    void setRadius_of_attack(float radius); // Sets the attack radius
    void setCost(int new_c); // Sets the Elixir cost to deploy
    void setisActive(bool active); // Sets the active state

    // Pure virtual draw method
    virtual void draw(sf::RenderWindow *window) = 0; // Draws the entity (must be implemented by derived classes)
};

#endif
