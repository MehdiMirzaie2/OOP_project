#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"
#include "UnitBuilder.hpp"


class Unit : public Entity
{
	protected:
        float HP;
		sf::Sprite skin;
		bool isPicked;

       // Weapon* weapon; // to be implemented

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
	

		void draw(sf::RenderWindow* window);
};

#endif