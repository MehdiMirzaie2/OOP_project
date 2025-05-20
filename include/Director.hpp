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
        // Unit* buildTank(std:: string customization);
        // Unit* buildMelee(std::string customization);

};

#endif // DIRECTOR_HPP_