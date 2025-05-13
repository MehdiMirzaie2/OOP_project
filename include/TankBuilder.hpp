#ifndef TANKBUILDER_HPP_
#define TANKBUILDER_HPP_

#include "UnitBuilder.hpp"

class TankBuilder : public UnitBuilder
{
    public:
        TankBuilder();
        void setCustomization(std:: string customization);
        Unit* build();
};

#endif // TANKBUILDER_HPP_