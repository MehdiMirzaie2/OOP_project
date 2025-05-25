#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Entity.hpp"
#include "Attack.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include "map.hpp"
#include <stack>

const sf::Vector2f UNITSIZE(0.06, 0.06);
typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;

class Map;

class Unit : public Entity
{
	protected:
        float HP;
		sf::Texture unitTextureIdle;
		sf::Texture unitTextureAttacking;
		std:: string projectileTextureName;
		int alliance;
		bool isPicked;
		// std::vector<Attack*> attacks;
		Unit* current_target;
		bool isAttacking;
		sf::Clock attackClock;
		sf::Time attackCooldown;
		bool isDead; 
		sf::Texture deadTexture;
		bool isMovingForward;
		sf::Vector2f m_deckPos;
		sf::Vector2i dydx;
		sf::Clock timeSinceDeath;

		sf::Clock attackAnimationHoldTime;

		sf::Clock MoveClock;

		// the path the unit will follow until their is distruption, then new path will be computed.
		std::stack<Pair> path;
		
       // Weapon* weapon; // to be implemente

	public:
		static std::vector<Attack*> active_attacks;
		// initialisers
		Unit();
		Unit(float dmg, float spd, sf::Vector2f location ,float radius_atk, int cst, int hp, std::string idleTextureName, std:: string attackingTextureName, std:: string projectileTextureName, int alliance); //unit builder has the values for the unit
		

		// getters
        float getHP();
		bool getisDead();
		sf::Sprite getSkin();
		Unit* getTarget();

		sf::Vector2f getDeckPosition();
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
		void updateSpriteLoc();
		//have to change the name of these two fucntinos at some stage
		void update(sf::Time time_passed);
		void update();
		void update(Map & map); //map is used for path finding
		
		void draw(sf::RenderWindow* window);
		sf::Sprite getSprite();

		void setDydx(sf::Vector2i);
		void setIsPicked(bool);
		void moveIfPicked(sf::Vector2i);
		void setDeckPosition(sf::Vector2f);
		//bool unitSellected(

		Pair getClosestTower();

		void setPath(std::stack<Pair> path);
		int getAlliance();
};

#endif
