#include "../../include/Deck.hpp"

Deck::Deck(int left_or_right)
{
    int left_pos;
    int alliance;
    if (left_or_right == 0)
    {
        left_pos = 50;
        alliance = 0;
    }
    else
    {
        left_pos = 1090;
        alliance = 1;
    }
    std::vector<Unit *> initialized_units;
    Unit *u1 = director.buildSwords(alliance);
    Unit *u2 = director.buildMage(alliance);
    Unit *u3 = director.buildShooter(alliance);
    Unit *u4 = director.buildTank(alliance);
    Unit *u5 = director.buildSwords(alliance);
    initialized_units.push_back(u1);
    initialized_units.push_back(u2);
    initialized_units.push_back(u3);
    initialized_units.push_back(u4);
    initialized_units.push_back(u5);

    for (long unsigned int i = 0; i < initialized_units.size(); i++)
    {
        if (initialized_units[i])
        {
            std::cout << "pushing unit\n";
            sf::Vector2f location(left_pos, (50 * i) + 100);
            initialized_units[i]->setLocation(location);
            initialized_units[i]->setDeckPosition(location);
            units.push_back(std::shared_ptr<Unit>(initialized_units[i]));
        }
        else
            std::cerr << "failed to build unit\n";
    }

    std::cout << "built deck\n";
}

Deck::Deck()
{
    int alliance = 1;
    std::vector<Unit *> initialized_units;
    Unit *u1 = director.buildSwords(alliance);
    Unit *u2 = director.buildMage(alliance);
    Unit *u3 = director.buildShooter(alliance);
    Unit *u4 = director.buildTank(alliance);
    Unit *u5 = director.buildSwords(alliance);
    initialized_units.push_back(u1);
    initialized_units.push_back(u2);
    initialized_units.push_back(u3);
    initialized_units.push_back(u4);
    initialized_units.push_back(u5);

    for (long unsigned int i = 0; i < initialized_units.size(); ++i)
    {
        /* not sure how to use builder */
        if (initialized_units[i])
        {
            std::cout << "pushing unit\n";
            sf::Vector2f location(50, (50 * i) + 100);
            initialized_units[i]->setLocation(location);
            units.push_back(std::shared_ptr<Unit>(initialized_units[i]));
        }
        else
            std::cerr << "failed to build unit\n";
    }
    std::cout << "built deck\n";
}

void Deck::draw(sf::RenderWindow *window)
{

    for (int i = 0; i < MAX_UNITS; i++)
    {
        // if (units[i]->getisActive()){
        units[i]->draw(window);
        //}
    }
}

std::vector<std::shared_ptr<Unit>> &Deck::getUnits()
{
    return units;
}

Unit *Deck::getPickedUnit()
{
    for (const auto &unit : units)
    {
        if (unit->getIsPicked())
            return unit.get();
    }
    return nullptr;
}

void Deck::swapDeployedUnit()
{
    for (int i = 0; i < units.size(); i++)
    {
        if (units[i]->getIsPicked())
            units[i] = std::shared_ptr<Unit>(&Unit(*units[i].get()));
    }
}