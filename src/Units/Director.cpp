#include "../../include/Director.hpp"

std::shared_ptr<Unit> Director::buildSwords(int alliance)
{
    return unitBuilder.withIdleTexture("swordm1.png")
                      .withAttackingTexture("swordm2.png")
                      .withProjectileTexture("swordslash.png")
                      .withRadius_of_attack(50)
                      .withAlliance(alliance)
                      .build();
}

std::shared_ptr<Unit> Director::buildShooter(int alliance)
{
    return unitBuilder.withIdleTexture("gunmo1.png")
                      .withAttackingTexture("gunmo2.png")
                      .withProjectileTexture("bullet.png")
                      .withRadius_of_attack(300)
                      .withAlliance(alliance)
                      .build();
}

std::shared_ptr<Unit> Director::buildMage(int alliance)
{
    return unitBuilder.withIdleTexture("mage_idle.png")
                       .withAttackingTexture("mage_attacking.png")
                       .withProjectileTexture("mage_projectile.png")
                       .withRadius_of_attack(200)
                       .withAlliance(alliance)
                       .build();
}

std::shared_ptr<Unit> Director::buildTank(int alliance)
{
    return unitBuilder.withIdleTexture("shield_idle.png")
                      .withAttackingTexture("shield_attacking.png")
                      .withProjectileTexture("shield_attack.png")
                      .withRadius_of_attack(10)
                      .withAlliance(alliance)
                      .build();
}

 std::shared_ptr<Unit> Director::buildKing(int alliance)
{
    if (alliance != 0 && alliance != 1){
        std::cout << "invalid alliance\n";
        return nullptr;
    }
    
    sf::Vector2f king_loc;

    if(alliance == 0) // 0 is left king
    {
        king_loc = sf::Vector2f(WINDOW_WIDTH/6, WINDOW_HEIGHT/2);
    }
    else if(alliance == 1) // 1 is right king
    {
        king_loc = sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH/6, WINDOW_HEIGHT/2);
    }
    
    
    return unitBuilder.withIdleTexture(std::to_string(alliance) + "king.png")
                      .withAttackingTexture(std::to_string(alliance) + "king.png")
                      .withProjectileTexture("king_arrow.png")
                      .withSpeed(0)
                      .withCost(0)
                      .withRadius_of_attack(200)
                      .withAlliance(alliance)
                      .withHP(500)
                      .withLocation(king_loc)
                      .build();
}

 std::shared_ptr<Unit> Director::buildTower(int alliance)
{
    return unitBuilder.withIdleTexture(std::to_string(alliance) + "tower.png")
                      .withAttackingTexture((std::to_string(alliance) + "tower.png"))
                      .withProjectileTexture("bullet.png")
                      .withSpeed(0)
                      .withCost(0)
                      .withRadius_of_attack(300)
                      .withAlliance(alliance)
                      .withHP(250)
                      .build();
                      
}
