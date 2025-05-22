#ifndef DIRECTOR_HPP_
#define DIRECTOR_HPP_

#include "UnitBuilder.hpp"

class Director 
{
    private:
        UnitBuilder unitBuilder;
// also a swordsman
    public:

        Unit* buildSwords();
        Unit* buildShooter();
        Unit* buildTank();
        Unit* buildMage();

};

#endif // DIRECTOR_HPP_