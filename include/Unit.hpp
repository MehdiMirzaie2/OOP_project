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
#include <unordered_set>

const sf::Vector2f UNITSIZE(0.06, 0.06); // Standard size for units

typedef std::pair<int, int> Pair; // Grid coordinates pair
typedef std::pair<double, std::pair<int, int>> pPair; // A* priority queue element

// Custom hash for Pair
struct pair_hash {
    std::size_t operator()(const Pair& p) const noexcept {
        // Combine hashes of the two ints (simple example)
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};

// Optionally, if you want custom equality, but std::pair already has operator==
// So this is optional.
struct pair_equal {
    bool operator()(const Pair& lhs, const Pair& rhs) const noexcept {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};


class Map;

class Unit : public Entity
{
protected:
    float m_HP; // Health points of the unit
    sf::Vector2f m_deckPos; // Position in the deck UI
    sf::Vector2i m_dydx; // Direction vector for movement
    sf::Clock m_timeSinceDeath; // Timer since unit died
    sf::Clock m_MoveClock; // Timer for movement timing
    sf::Clock m_attackClock; // Timer for attack cooldown
    sf::Time m_attackCooldown; // Time between attacks

    bool m_isTower = false; // Is this unit a tower?
    int m_alliance; // Team/alliance affiliation
    bool m_isPicked; // Whether unit is selected by the player
    Unit *m_current_target; // Current target unit for attack
    bool m_isAttacking; // Whether the unit is currently attacking
    bool m_isDead; // Whether the unit is dead
    bool m_isMovingForward; // Whether the unit is moving forward
    std::vector<Pair> targets;
    std::stack<Pair> m_path; // Path for unit movement

public:
    static std::vector<std::unique_ptr<Attack>> active_attacks; // List of active attacks in the game
    static std::vector<std::shared_ptr<Unit>> active_units; // List of active units in the game
    static std::unordered_set<Pair, pair_hash> dead_towers; // Set of dead towers

    // Constructors
    Unit(); // Default constructor
    Unit(const std::shared_ptr<Unit> &src);
    Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp, std::string idleTextureName, std::string attackingTextureName, std::string projectileTextureName, int alliance); // Parameterized constructor

    // Getters
    float getHP(); // Returns current health points
    bool getisDead(); // Returns whether the unit is dead
    sf::Sprite &getSkin(); // Returns reference to the unit’s sprite
    Unit *getTarget(); // Returns current attack target
    bool getIsPicked(); // Returns whether unit is selected
    bool getisTower(); // Returns whether unit is a tower
    sf::Sprite getSprite(); // Returns unit sprite copy
    int getAlliance(); // Returns unit alliance
	sf::Vector2f getDeckPosition(); // Returns position in deck UI

    // Setters
    void setHP(float newHP); // Sets health points
    void setisTower(bool isittower); // Sets tower status
    void setPath(std::stack<Pair> path); // Sets movement path
    void setDydx(sf::Vector2i); // Sets movement direction
    void setIsPicked(bool); // Sets selection status
    void setSkin(sf::Sprite new_skin); // Sets sprite skin
    void setDeckPosition(sf::Vector2f); // Sets position in deck UI

    // Utility methods
    void moveIfPicked(sf::Vector2i); // Moves unit if it is picked for drag and drop
    void updateAttackAnimation(); // Updates attack animation frames
    void updateSpriteLoc(); // Updates sprite location to match position
    void update(); // General update (movement, animation, etc.)
    void update(Map &map); // Updates unit behavior using pathfinding on map
    void attemptShooting(); // Attempts to shoot at target if possible
    void startMovingForward(); // Initiates forward movement
    void dead(); // Handles unit death logic
    void dying_animation(); // Plays dying animation
    void useAttack(Unit *hunted); // Performs attack on target unit
    void updateLocation(sf::Vector2f); // Updates the unit’s location
    void takeDamage(Attack attack); // Applies damage from an attack
    void describe(); // Prints unit information
    Pair getClosestTower(); // Finds closest tower on the map
    void draw(sf::RenderWindow *window); // Draws the unit on the screen

    //void bringToLife(sf::Vector2f pos, Map &gameMap); // Revives the unit at given position (commented out)
};

#endif
