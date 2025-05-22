#include "../../include/Director.hpp"

Unit* Director::buildSwords()
{
    return unitBuilder.withIdleTexture("swordm1.png")
                      .withAttackingTexture("swordm2.png")
                      .withProjectileTexture("swordslash.png")
                      .withRadius_of_attack(300)
                      .build();
}

Unit* Director::buildShooter()
{
    return unitBuilder.withIdleTexture("gunmo1.png")
                      .withAttackingTexture("gunmo2.png")
                      .withProjectileTexture("")
}


