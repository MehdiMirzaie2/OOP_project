#include "../../include/Director.hpp"

std::shared_ptr<Unit> Director::buildSwords(int alliance)
{
    return m_unitBuilder.withIdleTexture("swordm1.png")
        .withAttackingTexture("swordm2.png")
        .withProjectileTexture("swordslash.png")
        .withHP(120)                        // Increased HP
        .withDamage(25)                     // Increased Damage
        .withSpeed(0.25f)                   // Standard speed
        .withRadius_of_attack(70)           // Standard radius
        .withCost(2)                        // Low cost
        .withAlliance(alliance)
        .build();
}

std::shared_ptr<Unit> Director::buildShooter(int alliance)
{
    return m_unitBuilder.withIdleTexture("gunmo1.png")
        .withAttackingTexture("gunmo2.png")
        .withProjectileTexture("bullet.png")
        .withHP(80)                         // Lower HP
        .withDamage(30)                     // Good damage
        .withSpeed(0.3f)                    // Slightly faster
        .withRadius_of_attack(350)          // Long radius
        .withCost(4)                        // Higher cost
        .withAlliance(alliance)
        .build();
}

std::shared_ptr<Unit> Director::buildMage(int alliance)
{
    return m_unitBuilder.withIdleTexture("mage_idle.png")
        .withAttackingTexture("mage_attacking.png")
        .withProjectileTexture("mage_projectile.png")
        .withHP(90)                         // Moderate HP
        .withDamage(50)                     // High damage
        .withSpeed(0.2f)                    // Slightly slower
        .withRadius_of_attack(250)          // Good radius
        .withCost(5)                        // High cost
        .withAlliance(alliance)
        .build();
}

std::shared_ptr<Unit> Director::buildTank(int alliance)
{
    return m_unitBuilder.withIdleTexture("shield_idle.png")
        .withAttackingTexture("shield_attacking.png")
        .withProjectileTexture("shield_attack.png") 
        .withHP(300)                        // Very high HP
        .withDamage(15)                     // Lower damage
        .withSpeed(0.15f)                   // Slow speed
        .withRadius_of_attack(70)           // Short radius (melee focused)
        .withCost(6)                        // Highest cost for a standard unit
        .withAlliance(alliance)
        .build();
}


std::shared_ptr<Unit> Director::buildTower(int alliance)
{
    if (alliance != 0 && alliance != 1){
        std::cout << "Invalid alliance\n";
        return nullptr;
    }
    return m_unitBuilder.withIdleTexture(std::to_string(alliance) + "tower.png")
        .withAttackingTexture((std::to_string(alliance) + "tower.png"))
        .withProjectileTexture("bullet.png")
        .withSpeed(0)
        .withCost(0)
        .withRadius_of_attack(300)
        .withAlliance(alliance)
        .withHP(250)
        .build();
}
