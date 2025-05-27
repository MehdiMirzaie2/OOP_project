#include "../../include/Deck.hpp"

Deck::Deck(int left_or_right)
{
    int left_pos = left_or_right == 0 ? 50 : 1090;
    int alliance = left_or_right == 0 ? 0 : 1;

    m_units.insert(m_director.buildSwords(alliance));
    m_units.insert(m_director.buildMage(alliance));
    m_units.insert(m_director.buildShooter(alliance));
    m_units.insert(m_director.buildTank(alliance));
    m_units.insert(m_director.buildSwords(alliance));

    int i = 0;
    for (auto unit : m_units)
    {
        if (unit)
        {
            
            sf::Vector2f location(left_pos, (50 * i) + 100);
            unit->setLocation(location);
            unit->setDeckPosition(location);
        }
        else
            std::cerr << "failed to build unit\n";
        i++;
    }

    
}

Deck::Deck()
{
    int alliance = 1;
    // std::vector<Unit *> initialized_units;
    m_units.insert(m_director.buildSwords(alliance));
    m_units.insert(m_director.buildMage(alliance));
    m_units.insert(m_director.buildShooter(alliance));
    m_units.insert(m_director.buildTank(alliance));
    m_units.insert(m_director.buildSwords(alliance));

    int i = 0;
    for (auto unit : m_units)
    {
        if (unit)
        {
          
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
    for (auto unit : m_units)
        unit->draw(window);
}

std::set<std::shared_ptr<Unit>> &Deck::getUnits()
{
    return m_units;
}

std::shared_ptr<Unit> Deck::generateTowers(int alliance)
{
    return m_director.buildTower(alliance);
}

std::shared_ptr<Unit> Deck::getPickedUnit()
{
    for (const auto &unit : m_units)
    {
        if (unit->getIsPicked())
            return unit;
    }
    return nullptr;
}

void Deck::swapDeployedUnit(const std::shared_ptr<Unit> &unit)
{
    for (auto it = m_units.begin(); it != m_units.end(); ++it)
    {
        if (*it == unit)
        {
		std::cout << "calling swap\n";
            // std::shared_ptr<Unit> newUnit = m_director.buildSwords(unit->getAlliance());
            std::shared_ptr<Unit> newUnit = std::make_shared<Unit>(*unit);

            newUnit->setLocation(unit->getDeckPosition());
            newUnit->setDeckPosition(unit->getDeckPosition());
            m_units.erase(unit);
            m_units.insert(newUnit);
	    break;
        }
    }
}
