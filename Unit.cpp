#include "Unit.hpp"
#include "UnitBuilder.hpp"
#include <iostream>
#include <chrono>
#include <thread>

#define SOUL_SPEED 2

Unit::Unit() : Entity(), hpBar(100, 40, 8, 10) {} 

Unit::Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp,
           std::string idleTextureName, std::string attackingTextureName,
           std::string projectileTextureName, int alliance, float maxHP)
    : Entity(dmg, location.x, location.y, spd, radius_atk, cst),
      HP(hp),
      projectileTextureName(projectileTextureName),
      alliance(alliance),
      isPicked(false),
      current_target(nullptr),
      isAttacking(false),
      attackCooldown(sf::seconds(1)),
      isDead(false),
      isMovingForward(false),
      m_deckPos(),
      dydx(),
      timeSinceDeath(),
      hpBar(maxHP, 40, 8, 10),
      currentHP(maxHP)
{
    if (!unitTextureIdle.loadFromFile("src/Textures/" + idleTextureName)) {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!unitTextureAttacking.loadFromFile("src/Textures/" + attackingTextureName)) {
        std::cout << "Unable to load attacking texture!\n";
    }

    for (int i = 0; i < 5; i++) {
        attacks.emplace_back(this, projectileTextureName);
    }

    if (!deadTexture.loadFromFile("src/Textures/death.png")) {
        std::cout << "Could not load death soul texture.\n";
    }

    skin.setTexture(unitTextureIdle);
    skin.setScale(UNITSIZE); 
    updateSpriteLoc();
}

std::vector<Attack*> Unit::active_attacks = {};

void Unit::useAttack(Unit* /*hunted*/) {
    isAttacking = true;
}

void Unit::startMovingForward() {
    isMovingForward = true;
}

float Unit::getHP() {
    return HP;
}

void Unit::setHP(float newHP) {
    HP = newHP;
}

void Unit::setLocation(sf::Vector2i location) { // Override to ensure isActive is set correctly
    this->Entity::setLocation(location);
    updateSpriteLoc();
}

void Unit::updateLocation(sf::Vector2f location) {
    skin.setPosition(location);
}

void Unit::updateSpriteLoc() {
    skin.setPosition(static_cast<sf::Vector2f>(this->getLocation()));
}

bool Unit::getisDead() {
    return isDead;
}

void Unit::update(float deltaTime) {
    if (!isActive || isDead) return;

    skin.setTexture(isAttacking ? unitTextureAttacking : unitTextureIdle);

    if (isMovingForward) {
        sf::Vector2f current_pos = getFloatLoc();
        setLocation(sf::Vector2i(current_pos.x + speed * deltaTime, current_pos.y));
    }

    updateSpriteLoc();
    hpBar.setHP(currentHP);
}

void Unit::draw(sf::RenderWindow& window) {
    updateSpriteLoc();
    window.draw(skin);
    if (isAttacking) {
        attemptShooting();
    }
    hpBar.draw(window, skin.getPosition().x, skin.getPosition().y - 10);
}

sf::Sprite& Unit::getSprite() { // returns reference
   sprite.setScale(30.f / sprite.getTexture()->getSize().x, 30.f / sprite.getTexture()->getSize().y);
    return sprite;
}

sf::Sprite Unit::getSkin() {
    return skin;
}

void Unit::attemptShooting() {
    if (attackClock.getElapsedTime() >= attackCooldown) {
        for (auto& atk : attacks) {
            if (!atk.getisActive()) {
                attackClock.restart();
                atk.shoot(this->getFloatLoc());
                active_attacks.push_back(&atk);
                std::cout << "Attack added: " << atk.describe() << std::endl;
                break;
            }
        }
    }
}

void Unit::dead() {
    skin.setTexture(deadTexture);
    isDead = true;
}

void Unit::dying_animation() {}

void Unit::takeDamage(float amount) {
    currentHP = std::max(0.f, currentHP - amount);
    hpBar.setHP(currentHP);
}

void Unit::moveIfPicked(sf::Vector2i mouse_pos) {
    if (isPicked) {
        sf::Vector2i location(mouse_pos.x - dydx.x, mouse_pos.y - dydx.y);
        setLocation(location);
    }
}

void Unit::setIsPicked(bool status) {
    isPicked = status;
}

bool Unit::getisPicked() {
    return isPicked;
}

void Unit::setDydx(sf::Vector2i _dydx) {
    dydx = _dydx;
}
