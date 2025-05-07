#ifndef UNIT_HPP
#define UNIT_HPP

#include "Utils.hpp"

/*
the Unit class is the base class for all the deployables

We don't need skin, because all the abstractions are what would have used the skinnes for
*/
typedef struct s_unit t_unit;


/*struct to hold the coordinate of the unit*/

/*
using a struct so we can pack data easily
*/
struct s_unit {
	u_int32_t health;
	u_int32_t damage;
	u_int32_t speed;
	u_int32_t cost;
	s_location location;
}

#include <iostream>

class Unit
{
	private:
		t_unit values;
		// weapon

	public:
		// initialisers
		Unit();
		Unit(t_unit);
		Unit &operator=(const Unit &_src);
		Unit(const Unit &_src);
		~Unit();

		// getters
		u_int32_t get_health();
		u_int32_t get_damage();
		u_int32_t get_speed();
		u_int32_t get_cost();
		t_unit get_Unit();

		// setters
};

#endif