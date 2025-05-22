#ifndef MELEEBUILDER_HPP_
#define MELEEBUILDER_HPP_

#include "UnitBuilder.hpp"

class MeleeBuilder : public UnitBuilder
{
    public:
        MeleeBuilder();
        void setCustomization(std:: string customization);
        Unit* build();
};

#endif // MELEEBUILDER_HPP_