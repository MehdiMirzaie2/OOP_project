#ifndef DIRECTOR_HPP_
#define DIRECTOR_HPP_

#include "UnitBuilder.hpp"

class Director 
{
    private:
        UnitBuilder unitBuilder;
// also a swordsman
    public:

        Unit* buildSwords(int alliance);
        Unit* buildShooter(int alliance);
        Unit* buildTank(int alliance);
        Unit* buildMage(int alliance);
        Unit* buildTower(int alliance);
        Unit* buildKing(int alliance);

};

#endif // DIRECTOR_HPP_