#include "Units/header/Entity.hpp"
#include <iostream>

int main()
{
    Entity *newentity = new Entity(5, 10, 10, 2, 3, 1);
    std::cout << newentity->getCost() << " " << newentity->getLocation().x << newentity->getSpeed() << std::endl;
    newentity->setDamage(20);
    std::cout << newentity->getDamage() << std::endl;
    newentity->setLocation(new sf::Vector2f(1, 1));
    std::cout << newentity->getLocation().x << std::endl;
}