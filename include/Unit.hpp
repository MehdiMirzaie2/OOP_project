#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"
#include "Attack.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

const sf::Vector2f UNITSIZE(0.38, 0.38);

class Unit : public Entity
{
	protected:
        float HP;
		sf::Texture texture;
		sf::Sprite skin;
		bool isPicked;
		Attack* attacks;
		bool isAttacking;
		sf::Clock attackClock;
		sf::Time attackCooldown;

       // Weapon* weapon; // to be implemente

	public:

		// initialisers
		Unit();
		Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, std::string textureName); //unit builder has the values for the unit
		

		// getters
        float getHP();


		// setters
        void setHP(float newHP);
		void updateSpriteLoc();
		void useAttack();
		void attemptShooting();


		void draw(sf::RenderWindow* window);
};

#endif