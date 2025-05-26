#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Drawable.hpp"
#include <memory>

class Unit;

class Attack : public Drawable
// demo class for testing , might use for MVP
{
private:
    sf::Texture m_attackTexture;
    sf::Sprite m_attackSprite;
    float m_speed;
    bool m_isActive;
    int m_damage;
    Unit *m_owner;
    Unit *m_target;

public:
    Attack(Unit *owner, std::string attackTextureName, Unit *target);
    void move();
    bool getisActive();
    void draw(sf::RenderWindow *window);
    void updateLocation(sf::Vector2f new_loc);
    void shoot(sf::Vector2f shooting_location);
    void update();
    int getDamage();
    bool isHit(std::vector<std::shared_ptr<Unit>> unitlist);
    std::string describe();
};

#endif // ATTACK_HPP_