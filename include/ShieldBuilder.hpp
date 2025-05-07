#ifndef UNITS_HEADER_SHIELDBUILDER_HPP_
#define UNITS_HEADER_SHIELDBUILDER_HPP_

#include "UnitBuilder.hpp"

class ShieldBuilder : public UnitBuilder{
    private:
        Weapon* weapon = shield;
    
    public:
        Unit* Build();
}



#endif // UNITS_HEADER_SHIELDBUILDER_HPP_