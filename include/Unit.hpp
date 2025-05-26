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
#include <string>
const sf::Vector2f UNITSIZE(0.06, 0.06);
typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;

class Map;

class Unit : public Entity
{
protected:
	float m_HP;
	sf::Texture m_unitTextureIdle;
	sf::Texture m_unitTextureAttacking;
	sf::Texture m_deadTexture;
	sf::Vector2f m_deckPos;
	sf::Vector2i m_dydx;
	sf::Clock m_timeSinceDeath;
	sf::Clock m_MoveClock;
	sf::Clock m_attackClock;
	sf::Time m_attackCooldown;

	std::string m_projectileTextureName;
	std::string m_unitTextureIdleName;
	std::string m_unitTextureAttackingName;

	bool m_isTower = false;
	int m_alliance;
	bool m_isPicked;
	Unit *m_current_target;
	bool m_isAttacking;
	bool m_isDead;
	bool m_isMovingForward;
	std::stack<Pair> m_path; // the path the unit will follow until their is distruption, then new path will be computed.

public:
	
	static std::vector<std::unique_ptr<Attack>> active_attacks;
	static std::vector<std::shared_ptr<Unit>> active_units;
	// initialisers
	Unit();
	Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp, std::string idleTextureName, std::string attackingTextureName, std::string projectileTextureName, int alliance); // unit builder has the values for the unit
	// Unit(const Unit &src); //copy constructor
	//
	// virtual std::shared_ptr<Unit> clone() const {
	//	return std::make_shared<Unit>(*this);
	// }

	// getters
	float getHP();
	bool getisDead();
	sf::Sprite &getSkin();
	Unit *getTarget();
	bool getIsPicked();
	bool getisTower();
	sf::Sprite getSprite();
	int getAlliance();
	
	// setters
	void setHP(float newHP);
	void setisTower(bool isittower);
	void setPath(std::stack<Pair> path);
	void setDydx(sf::Vector2i);
	void setIsPicked(bool);
	void setSkin(sf::Sprite new_skin);
	void setDeckPosition(sf::Vector2f);

	//utils
	void moveIfPicked(sf::Vector2i);
	void updateAttackAnimation();
	void updateSpriteLoc();
	void update();
	void update(Map &map); // map is used for path finding
	void attemptShooting();
	void startMovingForward();
	void dead();
	void dying_animation();
	void useAttack(Unit *hunted);
	void updateLocation(sf::Vector2f);
	void takeDamage(Attack attack);
	sf::Vector2f getDeckPosition();
	void describe();
	Pair getClosestTower();
	void draw(sf::RenderWindow *window);
	// void bringToLife(sf::Vector2f pos, Map &gameMap);
};

#endif
