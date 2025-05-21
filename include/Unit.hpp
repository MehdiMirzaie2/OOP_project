#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"
#include "Attack.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

const sf::Vector2f UNITSIZE(0.1f, 0.1f);

class Unit : public Entity
{
	protected:
        float HP;
		sf::Texture unitTextureIdle;
		sf::Texture unitTextureAttacking;
		std:: string projectileTextureName;
		sf::Sprite skin;
		bool isPicked;
		// std::vector<Attack*> attacks;
		Unit* current_target;
		bool isAttacking;
		sf::Clock attackClock;
		sf::Time attackCooldown;
		bool isDead; 
		sf::Texture deadTexture;
		bool isMovingForward;
		sf::Clock timeSinceDeath;
       // Weapon* weapon; // to be implemente

	public:
		static std::vector<Attack*> active_attacks;
		// initialisers
		Unit();
		Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, std::string idleTextureName, std:: string attackingTextureName, std:: string projectileTextureName); //unit builder has the values for the unit
		

		// getters
        float getHP();
		bool getisDead();
		sf::Sprite getSkin();
		Unit* getTarget();

		// setters
        void setHP(float newHP);
		void updateSpriteLoc();
		void useAttack(Unit* hunted);
		void attemptShooting();
		void startMovingForward();

		void dead();
		void dying_animation();
		void takeDamage(Attack attack);

		void update(sf::Time time_passed);
		void draw(sf::RenderWindow* window);
};

#endif