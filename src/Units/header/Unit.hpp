// #ifndef UNIT_HPP
// #define UNIT_HPP

// /*
// the Unit class is the base class for all the deployables

// We don't need skin, because all the abstractions are what would have used the skinnes for
// */

// /*struct to hold the coordinate of the unit*/
// struct Location {
// 	int rows;
// 	int cols;
// };

// /*
// using a struct so we can pack data easily
// */
// struct Unit_struct {
// 	u_int32_t health;
// 	u_int32_t damage;
// 	u_int32_t speed;
// 	u_int32_t cost;
// 	Location location;
// }

// #include <iostream>

// class Unit
// {
// 	private:
		
// 		// weapon

// 	public:
// 		// initialisers
// 		Unit();
// 		Unit(Unit_struct);
// 		Unit &operator=(const Unit &_src);
// 		Unit(const Unit &_src);
// 		~Unit();

// 		// getters
// 		u_int32_t get_health();
// 		u_int32_t get_damage();
// 		u_int32_t get_speed();
// 		u_int32_t get_cost();
// 		Unit_struct get_Unit();

// 		// setters
// };

// #endif