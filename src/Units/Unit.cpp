#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, sf::Sprite skin) : Entity(dmg, loc_x, loc_y, spd, radius_atk, cst), HP(hp), skin(skin), isPicked(false) {};


float Unit::getHP()
{
    return HP;
};

void Unit::setHP(float newHP)
{
    HP = newHP;
}



void Unit::draw(sf::RenderWindow* window){
    window->draw(skin);
}

