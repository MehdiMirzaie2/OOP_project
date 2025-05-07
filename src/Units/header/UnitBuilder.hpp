#ifndef UNITS_HEADER_UNITBUILDER_HPP_
#define UNITS_HEADER_UNITBUILDER_HPP_

#include "Unit.hpp"

class UnitBuilder // Provides interface for concrete unit builders
{
    protected:
        float HP;
        float damage; 
        std::unique_ptr<sf::Vector2f> location;
        //location = default location (provide default placement for units)
        float speed;
        float radius_of_attack;
        int cost;
        Weapon* weapon; // To be implemented

    public: 
        
        // Builder Params
        UnitBuilder& withHP(float hp);
        UnitBuilder&  withDamage(float new_dmg);
        UnitBuilder&  withSpeed(float new_sp);
        UnitBuilder&  withLocation(sf::Vector2f *newloc);
        UnitBuilder&  withRadius_of_attack(float radius);
        UnitBuilder&  withCost(int new_c); 
        virtual UnitBuilder& withWeapon(Weapon* new_weapon) = 0; // make abstract as it is different for each subbuilder.
        
        // Joining all the components
        virtual Unit* build() = 0; // Different for all subclass builders
}

#endif // UNITS_HEADER_UNITBUILDER_HPP_