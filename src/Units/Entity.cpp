#include "../../include/Entity.hpp"

Entity::Entity(): Drawable() {}; // does nothing atm because I dont know what to put as the default values yet.

Entity::Entity(std::string a, std::string b, std::string c, float dmg, sf::Vector2f location, float spd, float radius_atk, int cst) : Drawable(a, b, c)
{
    m_damage = dmg;
    m_skin.setPosition(location);
    m_speed = spd;
    m_radius_of_attack = radius_atk;
    m_isActive = false;
    m_cost = cst;
}

void Entity::setisActive(bool active) { m_isActive = active; };
bool Entity::getisActive() { return m_isActive; };

sf::Vector2f Entity::getLocation() { return m_skin.getPosition(); };
void Entity::setLocation(sf::Vector2f new_loc) { m_skin.setPosition(new_loc); };

float Entity::getDamage() { return m_damage; };
void Entity::setDamage(float new_dmg) { m_damage = new_dmg; };

float Entity::getSpeed() { return m_speed; };
void Entity::setSpeed(float new_sp) { m_speed = new_sp; };

float Entity::getRadius_of_attack() { return m_radius_of_attack; };
void Entity::setRadius_of_attack(float radius) { m_radius_of_attack = radius; };

int Entity::getCost() { return m_cost; };
void Entity::setCost(int new_c) { m_cost = new_c; };
