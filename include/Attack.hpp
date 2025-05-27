#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Drawable.hpp"
#include <memory>

class Unit;

class Attack
{
private:
    sf::Texture m_attackTexture;
    sf::Sprite m_attackSprite;
    float m_speed;
    bool m_isActive;
    int m_damage;
    Unit *m_owner;
    Unit *m_target;

public:
    Attack(Unit *owner, std::string attackTextureName, Unit *target); // Constructor to initialize the attack with owner, texture, and target
    void move(); // Moves the attack towards the target
    bool getisActive(); // Returns whether the attack is currently active
    void draw(sf::RenderWindow *window); // Draws the attack sprite to the window
    void updateLocation(sf::Vector2f new_loc); // Updates the attack's position
    void shoot(sf::Vector2f shooting_location); // Sets the initial shooting location
    void update(); // Updates the attack's state (movement, collision, etc.)
    int getDamage(); // Returns the damage this attack deals
    bool isHit(std::vector<std::shared_ptr<Unit>> unitlist); // Checks if the attack hits any unit in the list
    std::string describe(); // Returns a string description of the attack
};

#endif // ATTACK_HPP_
