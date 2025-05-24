#include "../../include/Director.hpp"

Unit* Director::buildSwords(int alliance)
{
    return unitBuilder.withIdleTexture("swordm1.png")
                      .withAttackingTexture("swordm2.png")
                      .withProjectileTexture("swordslash.png")
                      .withRadius_of_attack(50)
                      .withAlliance(alliance)
                      .build();
}

Unit* Director::buildShooter(int alliance)
{
    return unitBuilder.withIdleTexture("gunmo1.png")
                      .withAttackingTexture("gunmo2.png")
                      .withProjectileTexture("bullet.png")
                      .withRadius_of_attack(300)
                      .withAlliance(alliance)
                      .build();
}

Unit* Director::buildMage(int alliance)
{
    return unitBuilder.withIdleTexture("mage_idle.png")
                       .withAttackingTexture("mage_attacking.png")
                       .withProjectileTexture("mage_projectile.png")
                       .withRadius_of_attack(200)
                       .withAlliance(alliance)
                       .build();
}

Unit* Director::buildTank(int alliance)
{
    return unitBuilder.withIdleTexture("shield_idle.png")
                      .withAttackingTexture("shield_attacking.png")
                      .withProjectileTexture("shield_attack.png")
                      .withRadius_of_attack(10)
                      .withAlliance(alliance)
                      .build();
}


