#ifndef UNIT_HPP
#define UNIT_HPP

/*
the Unit class is the base class for all the deployables

We don't need skin, because all the abstractions are what would have used the skinnes for
*/

#include <iostream>
#include "Entity.hpp"

class Unit : public Entity
{
	protected:
        float HP;
        Weapon* weapon; // to be implemented

	public:

		// initialisers
		Unit();
		Unit(UnitBuilder unitBuilder); //unit builder has the values for the unit
		Unit &operator=(const Unit &_src);
		Unit(const Unit &_src);
		~Unit();

		// getters
        float getHP();

		// setters
        void setHP(float newHP);
};

#endif