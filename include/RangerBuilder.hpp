#ifndef RANGERBUILDER_HPP_
#define RANGERBUILDER_HPP_

#include "UnitBuilder.hpp"

class RangerBuilder : public UnitBuilder
{
    public:
        RangerBuilder();
        void setCustomization(std:: string customization);
        Unit* build();
};


#endif // RANGERBUILDER_HPP_