#include "../../include/Director.hpp"

Unit* Director::buildSwords()
{
    return unitBuilder.withIdleTexture("swordm1.png")
                      .withAttackingTexture("swordm2.png")
                      .withProjectileTexture("swordslash.png")
                      .build();
}



