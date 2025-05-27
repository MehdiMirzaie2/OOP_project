#ifndef UNITS_HEADER_UNITBUILDER_HPP_
#define UNITS_HEADER_UNITBUILDER_HPP_

#include "Unit.hpp"

class UnitBuilder // Builder pattern to construct Unit objects step-by-step
{
protected:
    float m_HP = 100; // Unit health points
    float m_damage = 20; // Unit damage value
    sf::Vector2f m_location; // Unit spawn location
    int m_alliance; // Unit team/alliance ID
    float m_speed = 0.25; // Unit movement speed
    float m_radius_of_attack = 20; // Attack range radius
    int m_cost = 2; // Unit deployment cost
    std::string m_textureIdle; // Texture name when idle
    std::string m_textureAttacking; // Texture name when attacking
    std::string m_projectileTextureName; // Projectile texture name

public:
    // Builder setters with method chaining
    UnitBuilder &withAlliance(int alliance); // Sets unit alliance
    UnitBuilder &withIdleTexture(std::string IdletextureName); // Sets idle texture
    UnitBuilder &withAttackingTexture(std::string attackingTextureName); // Sets attacking texture
    UnitBuilder &withHP(float hp); // Sets health points
    UnitBuilder &withDamage(float new_dmg); // Sets damage amount
    UnitBuilder &withSpeed(float new_sp); // Sets movement speed
    UnitBuilder &withLocation(sf::Vector2f newloc); // Sets spawn location
    UnitBuilder &withRadius_of_attack(float radius); // Sets attack radius
    UnitBuilder &withCost(int new_c); // Sets deployment cost
    UnitBuilder &withProjectileTexture(std::string projectileTexture); // Sets projectile texture

    std::shared_ptr<Unit> build(); // Constructs and returns the configured Unit object
};

#endif // UNITS_HEADER_UNITBUILDER_HPP_
