#include "../../include/RangerBuilder.hpp"

RangerBuilder::RangerBuilder()
{
    HP = 200;
    damage = 150;
    speed = 5;
    radius_of_attack = 20;
    cost = 4;
    setCustomization("archer");
}

void RangerBuilder::setCustomization(std:: string customization)
// sets the specific customization defaults, like if the string is 'Archer' sets archer specific stats and gives bow as the weapon.
{
    // implement unordered map here
    if (customization == "archer"){
        textureName = "chr_archer_sprite_023.png";
    }
    std:: cout << "Customization used: " << customization << std:: endl;
};

Unit* RangerBuilder::build(){
    return new Unit(damage, location.x, location.y, speed, radius_of_attack, cost, HP, textureName);
}