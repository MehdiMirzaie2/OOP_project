#ifndef UNITS_HEADER_RANGERBUILDER_HPP_
#define UNITS_HEADER_RANGERBUILDER_HPP_

#include "UnitBuilder.hpp"

class RangerBuilder : public UnitBuilder{
    private:
        Weapon* weapon = gun;

    public:
        Unit* Build();
}

#endif // UNITS_HEADER_RANGERBUILDER_HPP_