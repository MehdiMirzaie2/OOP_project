#ifndef UNITS_HEADER_UNITBUILDER_HPP_
#define UNITS_HEADER_UNITBUILDER_HPP_

#include "Unit.hpp"

class UnitBuilder // Provides interface for concrete unit builders
{

protected:
    float HP = 100; // 5 Ranged Attacks
    float damage = 20;
    sf::Vector2f location;
    int alliance;
    float speed = 0.25;
    float radius_of_attack = 20;
    int cost = 2;
    std::string textureIdle;
    std::string textureAttacking;
    std::string projectileTextureName;

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