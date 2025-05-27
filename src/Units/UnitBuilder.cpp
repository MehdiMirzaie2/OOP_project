#include "../../include/UnitBuilder.hpp"

UnitBuilder &UnitBuilder::withHP(float hp)
{
    m_HP = hp;
    return *this;
};
UnitBuilder &UnitBuilder::withDamage(float new_dmg)
{
    m_damage = new_dmg;
    return *this;
};
UnitBuilder &UnitBuilder::withSpeed(float new_sp)
{
    m_speed = new_sp;
    return *this;
};
UnitBuilder &UnitBuilder::withLocation(sf::Vector2f newloc)
{
    m_location = newloc;
    return *this;
};
UnitBuilder &UnitBuilder::withRadius_of_attack(float radius)
{
    m_radius_of_attack = radius;
    return *this;
};
UnitBuilder &UnitBuilder::withCost(int new_c)
{
    m_cost = new_c;
    return *this;
};

UnitBuilder &UnitBuilder::withIdleTexture(std::string IdletextureName)
{
    m_textureIdle = IdletextureName;
    return *this;
}

UnitBuilder &UnitBuilder::withAttackingTexture(std::string attackingTextureName)
{
    m_textureAttacking = attackingTextureName;
    return *this;
}

UnitBuilder &UnitBuilder::withProjectileTexture(std:: string projectileTexture)
{
    m_projectileTextureName = projectileTexture;
    return *this;
}

UnitBuilder &UnitBuilder::withAlliance(int alliance)
{
    m_alliance = alliance;
    return *this;
}

std::shared_ptr<Unit> UnitBuilder::build()
{
    std::shared_ptr<Unit> unit = std::make_shared<Unit>(m_damage, m_speed, m_location, m_radius_of_attack, m_cost, m_HP, m_textureIdle, m_textureAttacking, m_projectileTextureName, m_alliance);
    return unit;
}
