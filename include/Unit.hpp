#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"
#include "Attack.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

const sf::Vector2f UNITSIZE(-(30.f / 130.f), 30.f / 135.f);

class Unit : public Entity
{
	protected:
        float HP;
		sf::Texture unitTextureIdle;
		sf::Texture unitTextureAttacking;
		std:: string projectileTextureName;
		
		bool isPicked;
		// std::vector<Attack*> attacks;
		Unit* current_target;
		bool isAttacking;
		sf::Clock attackClock;
		sf::Time attackCooldown;
		bool isDead; 
		sf::Texture deadTexture;
		bool isMovingForward;
		sf::Vector2i deckPos;
		sf::Vector2i dydx;
		sf::Clock timeSinceDeath;
		
       // Weapon* weapon; // to be implemente

	public:
		static std::vector<Attack*> active_attacks;
		// initialisers
		Unit();
		Unit(float dmg, float spd, sf::Vector2f location ,float radius_atk, int cst, int hp, std::string idleTextureName, std:: string attackingTextureName, std:: string projectileTextureName); //unit builder has the values for the unit
		

		// getters
        float getHP();
		bool getisDead();
		sf::Sprite getSkin();
		Unit* getTarget();

		// setters
        void setHP(float newHP);
		
		
		void useAttack(Unit* hunted);
		void attemptShooting();
		void startMovingForward();

		void dead();
		void dying_animation();
		void takeDamage(Attack attack);

		void updateLocation(sf::Vector2f);
		bool getIsPicked();
		

		//have to change the name of these two fucntinos at some stage
		void update(sf::Time time_passed);
		void update();
		
		void draw(sf::RenderWindow* window);
		sf::Sprite getSprite();

		void setDydx(sf::Vector2i);
		void setIsPicked(bool);
		void moveIfPicked(sf::Vector2i);
		//bool unitSellected(
};

#endif
