#ifndef DIRECTOR_HPP_
#define DIRECTOR_HPP_

#include "RangerBuilder.hpp"
#include "TankBuilder.hpp"
#include "MeleeBuilder.hpp"

class Director 
{
    private:
        RangerBuilder rangerbuilder;
        // MeleeBuilder meleebuilder;
        // TankBuilder tankbuilder;
// also a swordsman
    public:

        Unit* buildRanger(std::string customization);
        // Unit* buildTank(std:: string customization);
        // Unit* buildMelee(std::string customization);

};

#endif // DIRECTOR_HPP_