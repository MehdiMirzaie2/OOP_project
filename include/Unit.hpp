#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"

class Unit : public Entity
{
	protected:
        float HP;
       // Weapon* weapon; // to be implemented

	public:

		// initialisers
		Unit();
		//Unit(UnitBuilder unitBuilder); //unit builder has the values for the unit
		Unit &operator=(const Unit &_src);
		Unit(const Unit &_src);
		~Unit();

		// getters
        float getHP();

		// setters
        void setHP(float newHP);

		virtual void deploy(sf::Vector2f d_loc) = 0; //abstract class
};

#endif