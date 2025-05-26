#ifndef UNITS_HEADER_UNITBUILDER_HPP_
#define UNITS_HEADER_UNITBUILDER_HPP_

#include "Unit.hpp"

class UnitBuilder // Provides interface for concrete unit builders
{

protected:
    float m_HP = 100; // 5 Ranged Attacks
    float m_damage = 20;
    sf::Vector2f m_location;
    int m_alliance;
    float m_speed = 0.25;
    float m_radius_of_attack = 20;
    int m_cost = 2;
    std::string m_textureIdle;
    std::string m_textureAttacking;
    std::string m_projectileTextureName;

public:
    // Builder Params
    UnitBuilder &withAlliance(int alliance);
    UnitBuilder &withIdleTexture(std::string IdletextureName);
    UnitBuilder &withAttackingTexture(std::string attackingTextureName);
    UnitBuilder &withHP(float hp);
    UnitBuilder &withDamage(float new_dmg);
    UnitBuilder &withSpeed(float new_sp);
    UnitBuilder &withLocation(sf::Vector2f newloc);
    UnitBuilder &withRadius_of_attack(float radius);
    UnitBuilder &withCost(int new_c);
    UnitBuilder &withProjectileTexture(std::string projectileTexture);
    std::shared_ptr<Unit> build();
};

#endif // UNITS_HEADER_UNITBUILDER_HPP_