#include "../../include/RangerBuilder.hpp"

void RangerBuilder::setCustomization(std:: string customization)
// sets the specific customization defaults, like if the string is 'Archer' sets archer specific stats and gives bow as the weapon.
{
    std:: cout << "Customization used: " << customization << std:: endl;
};

RangerBuilder::RangerBuilder()
{
    HP = 200;
    damage = 150;
    speed = 5;
    radius_of_attack = 20;
    cost = 4;
    sf::Texture texture;
    if (!texture.loadFromFile("src/Textures/Ranger-nobg.png")){
        std::cout << "Unable to load texture!\n";
    }
    skin = sf::Sprite(texture);
}

Unit* RangerBuilder::build(){
    return new Unit(damage, location.x, location.y, speed, radius_of_attack, cost, HP, skin);
}