#include "../../include/Attack.hpp"
#include "../../include/Unit.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

Attack::Attack(Unit *owner, std::string attackTextureName, Unit *target)
{
    if (!m_attackTexture.loadFromFile("src/Textures/" + attackTextureName))
    {
        std::cout << "Unable to load attack texture: src/Textures/" << attackTextureName << std::endl;
    }
    
    m_isActive = false;
    m_damage = 20;
    m_speed = 0.5;
    m_attackSprite.setOrigin(m_attackTexture.getSize().x / 2.f, m_attackTexture.getSize().y / 2.f);
    m_attackSprite.setTexture(m_attackTexture);
    int flip = target->getAlliance() == 0 ? 1 : -1;
    m_attackSprite.setScale(flip * 0.06f, 0.06f);
    m_owner = owner;
    m_target = target;
}

void Attack::shoot(sf::Vector2f shooting_location)
{
    m_attackSprite.setPosition(shooting_location);
    m_isActive = true;
}

void Attack::move()
{
    sf::Vector2f location = m_attackSprite.getPosition();
    float displacement_x = m_target->getLocation().x - location.x;
    float displacement_y = m_target->getLocation().y - location.y;

    // To calculate the unit vector for direction, as the above vector is not a unit vector, we divide by distance

    float distance = std::sqrt((displacement_x * displacement_x) + (displacement_y * displacement_y));
    float normalized_displacement_x = displacement_x / distance;
    float normalized_displacement_y = displacement_y / distance;

    m_attackSprite.move(sf::Vector2f(normalized_displacement_x * m_speed, normalized_displacement_y * m_speed));
}

bool Attack::getisActive() { return m_isActive; };

int Attack::getDamage() { return m_damage; };

void Attack::updateLocation(sf::Vector2f new_loc)
{
    m_attackSprite.setPosition(new_loc);
}

void Attack::draw(sf::RenderWindow *window)
{
    window->draw(m_attackSprite);
}

void Attack::update()
{
    if (getisActive())
    {
        move();
    }
}

bool Attack::isHit(std::vector<std::shared_ptr<Unit>> unitlist)
{
    sf::FloatRect collision_box = m_attackSprite.getGlobalBounds();
    for (auto unit: unitlist)
    {
        //Unit *unit_ptr = unitlist[i].get();
        if (m_owner == unit.get() || unit->getisDead())
        {
            continue;
        }
        if (collision_box.intersects(unit->getSkin().getGlobalBounds()))
        {
            m_isActive = false;
            if (unit->getisActive())
            {
                unit->takeDamage(*this);
               
                auto it = std::find_if(Unit::active_attacks.begin(), Unit::active_attacks.end(),
                                       [this](const std::unique_ptr<Attack> &p_attack)
                                       {
                                           return p_attack.get() == this;
                                       });

                if (it != Unit::active_attacks.end())
                {
                    Unit::active_attacks.erase(it); // Erase the unique_ptr; this will delete the Attack object
                }
                return true;
            }
        }
    }
    return false;
}

std::string Attack::describe()
{
    std::string exist = "The attack is exist!\n";
    return exist;
}
