#include "../../include/Director.hpp"


Unit* Director::buildRanger(std::string customization)
{
    rangerbuilder.setCustomization(customization);
    return rangerbuilder.build();
}

