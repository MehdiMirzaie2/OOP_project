#include "../../include/Deck.hpp"

Deck::Deck(int left_or_right)
{
    int left_pos = left_or_right == 0 ? 50 : 1090;
    int alliance = left_or_right == 0 ? 0 : 1;

    units.insert(director.buildSwords(alliance));
    units.insert(director.buildMage(alliance));
    units.insert(director.buildShooter(alliance));
    units.insert(director.buildTank(alliance));
    units.insert(director.buildSwords(alliance));

    int i = 0;
    for (auto unit : units)
    {
        if (unit)
        {
            std::cout << "pushing unit\n";
            sf::Vector2f location(left_pos, (50 * i) + 100);
            unit->setLocation(location);
            unit->setDeckPosition(location);
        }
        else
            std::cerr << "failed to build unit\n";
        i++;
    }

    std::cout << "built deck\n";
}

Deck::Deck()
{
    int alliance = 1;
    // std::vector<Unit *> initialized_units;
    units.insert(director.buildSwords(alliance));
    units.insert(director.buildMage(alliance));
    units.insert(director.buildShooter(alliance));
    units.insert(director.buildTank(alliance));
    units.insert(director.buildSwords(alliance));

    int i = 0;
    for (auto unit : units)
    {
        /* not sure how to use builder */
        if (unit)
        {
            std::cout << "pushing unit\n";
            sf::Vector2f location(50, (50 * i) + 100);
            unit->setLocation(location);
        }
        else
            std::cerr << "failed to build unit\n";
        i++;
    }
    std::cout << "built deck\n";
}

void Deck::draw(sf::RenderWindow *window)
{
    for (auto unit : units)
        unit->draw(window);
}

std::set<std::shared_ptr<Unit>> &Deck::getUnits()
{
    return units;
}

std::shared_ptr<Unit> Deck::generateKing(int alliance)
{
    return director.buildKing(alliance);
}

std::shared_ptr<Unit> Deck::generateTowers(int alliance)
{
    return director.buildTower(alliance);
}

std::shared_ptr<Unit> Deck::getPickedUnit()
{
    for (const auto &unit : units)
    {
        if (unit->getIsPicked())
            return unit;
    }
    return nullptr;
}

void Deck::swapDeployedUnit(const std::shared_ptr<Unit> &unit)
{
    for (auto m_unit : units)
    {
        if (m_unit == unit)
        {
            std::shared_ptr<Unit> newUnit = director.buildSwords(unit->getAlliance());
            newUnit->setLocation(unit->getDeckPosition());
            newUnit->setDeckPosition(unit->getDeckPosition());
            units.erase(unit);
            units.insert(newUnit);
        }
    }
}
