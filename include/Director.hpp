#ifndef DIRECTOR_HPP_
#define DIRECTOR_HPP_

#include "UnitBuilder.hpp"

class Director
{
private:
        UnitBuilder m_unitBuilder;
        // also a swordsman

public:
        std::shared_ptr<Unit> buildSwords(int alliance); // Builds and returns a swordsman unit for the given alliance
        std::shared_ptr<Unit> buildShooter(int alliance); // Builds and returns a shooter unit for the given alliance
        std::shared_ptr<Unit> buildTank(int alliance); // Builds and returns a tank unit for the given alliance
        std::shared_ptr<Unit> buildMage(int alliance); // Builds and returns a mage unit for the given alliance
        std::shared_ptr<Unit> buildTower(int alliance); // Builds and returns a tower unit for the given alliance
};

#endif // DIRECTOR_HPP_
