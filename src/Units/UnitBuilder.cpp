#include "../../include/UnitBuilder.hpp"

UnitBuilder &UnitBuilder::withHP(float hp)
{
    HP = hp;
    return *this;
};
UnitBuilder &UnitBuilder::withDamage(float new_dmg)
{
    damage = new_dmg;
    return *this;
};
UnitBuilder &UnitBuilder::withSpeed(float new_sp)
{
    speed = new_sp;
    return *this;
};
UnitBuilder &UnitBuilder::withLocation(sf::Vector2i newloc)
{
    location = newloc;
    return *this;
};
UnitBuilder &UnitBuilder::withRadius_of_attack(float radius)
{
    radius_of_attack = radius;
    return *this;
};
UnitBuilder &UnitBuilder::withCost(int new_c)
{
    cost = new_c;
    return *this;
};

UnitBuilder &UnitBuilder::withIdleTexture(std::string IdletextureName)
{
    this->textureIdle = IdletextureName;
    return *this;
}

UnitBuilder &UnitBuilder::withAttackingTexture(std::string attackingTextureName)
{
    this->textureAttacking = attackingTextureName;
    return *this;
}

UnitBuilder &UnitBuilder::withProjectileTexture(std:: string projectileTexture)
{
    projectileTextureName = projectileTexture;
    return *this;
}

Unit* UnitBuilder::build()
{
    return new Unit(damage, location.x, location.y, speed, radius_of_attack, cost, HP, textureIdle, textureAttacking, projectileTextureName);
}