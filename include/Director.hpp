#ifndef DIRECTOR_HPP_
#define DIRECTOR_HPP_

#include "UnitBuilder.hpp"

class Director 
{
    private:
        UnitBuilder unitBuilder;
// also a swordsman
    public:

        std::shared_ptr<Unit> buildSwords(int alliance);
        std::shared_ptr<Unit> buildShooter(int alliance);
        std::shared_ptr<Unit> buildTank(int alliance);
        std::shared_ptr<Unit> buildMage(int alliance);

};

#endif // DIRECTOR_HPP_