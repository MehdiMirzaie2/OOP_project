#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"


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
		Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, sf::Sprite skin); //unit builder has the values for the unit
		

		// getters
        float getHP();


		// setters
        void setHP(float newHP);
		
		void draw(sf::RenderWindow* window);
};

#endif