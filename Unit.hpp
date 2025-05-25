#ifndef UNIT_HPP_
#define UNIT_HPP_

#include "Entity.hpp"
#include "HPBar.hpp"
#include "Attack.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#define UNITSIZE  sf::Vector2f(1.f, 1.f)

class Unit : public Entity {
private:
    float HP;
    float currentHP;
    std::string projectileTextureName;
    int alliance;
    bool isPicked;
    bool isAttacking;
    bool isDead;
    bool isMovingForward;

    sf::Texture unitTextureIdle, unitTextureAttacking, deadTexture;
    sf::Sprite skin;
    sf::Sprite sprite; // Used in getSprite()
    sf::Clock attackClock;
    sf::Time attackCooldown;

    sf::Vector2i m_deckPos;
    sf::Vector2i dydx;
    sf::Time timeSinceDeath;

    Unit* current_target;

    HPBar hpBar;
    std::vector<Attack> attacks;

public:
    static std::vector<Attack*> active_attacks;

    Unit();
    Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp,
         std::string idleTextureName, std::string attackingTextureName,
         std::string projectileTextureName, int alliance, float maxHP);

    void useAttack(Unit* hunted);
    void attemptShooting();
    void startMovingForward();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void takeDamage(float amount);
    void dead();
    void dying_animation();

    float getHP();
    void setHP(float newHP);

    sf::Sprite& getSprite();
    sf::Sprite getSkin();

    void setLocation(sf::Vector2i location);
    void updateLocation(sf::Vector2f location);
    void updateSpriteLoc();

    bool getisDead();

    void moveIfPicked(sf::Vector2i mouse_pos);
    void setIsPicked(bool status);
    bool getisPicked();
    void setDydx(sf::Vector2i _dydx);
};

#endif // UNIT_HPP_
