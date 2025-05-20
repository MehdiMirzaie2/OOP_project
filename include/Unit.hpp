#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"

//const sf::Vector2f UNITSIZE(0.38, 0.38);
const sf::Vector2f UNITSIZE(-(30.f / 130.f), 30.f / 135.f);
class Unit : public Entity
{
	protected:
        float HP;
		sf::Texture texture;
		sf::Sprite skin;
		bool isPicked;
		

       // Weapon* weapon; // to be implemente

	public:

		// initialisers
		Unit();
		Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, std::string textureName); //unit builder has the values for the unit
		

		// getters
        float getHP();


		// setters
        void setHP(float newHP);
	void updateLocation(sf::Vector2f);
	void updateSpriteLoc();
		
		void draw(sf::RenderWindow* window);
};

#endif
