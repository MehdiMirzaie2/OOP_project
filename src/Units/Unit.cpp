#include "../../include/Unit.hpp"

Unit::Unit() : Entity() {};

Unit::Unit(UnitBuilder unitBuilder) : Entity(unitBuilder.dmg, unitBuilder.loc_x, unitBuilder.loc_y, unitBuilder.spd, unitBuilder.radius_atk, unitBuilder.cst), HP(unitBuilder.hp), skin(unitBuilder.sprite), isPicked(false) {};

Unit &Unit::operator=(const Unit &_src)
{
    std::cout << "unit copy assignment constructor called\n";
}

Unit::Unit(const Unit &_src)
{
    std::cout << "unit copy constructor called\n";
}

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

Unit::~Unit()
{
    std::cout << "unit destructor called\n";
}