#ifndef BATTLEWINDOW_HPP_
#define BATTLEWINDOW_HPP_

#include "Window.hpp"
#include "map.hpp"
#include "Director.hpp"
#include "User.hpp"
#include "Unit.hpp"

class BattleWindow : public Window
// Renders the battle visuals like the map.
{
private:
    Map m_gameMap;
    Director m_director;
    int m_turn;
    User* m_user1;
    User* m_user2;
    sf::Clock m_gameClock;

    void deploye(sf::Event); // Handles unit deployment based on user input
    void selectUnit(sf::Event); // Handles unit selection logic

public:
    static int winner;
    ~BattleWindow();    
    BattleWindow(); // Constructor to initialize the battle window
    void draw_all(sf::RenderWindow *window); // Draws all battle elements to the window
    int runWindow(); // Main loop to run the battle window
    void checkCollisions(); // Checks for collisions between units and attacks
    void checkWinner(); // Checks if the game has been won
    void updateUnits(); // Updates all units' states
    void updateAttacks(); // Updates all active attacks
    void startUnitAttack(Unit *attacker); // Initiates an attack from the specified unit
};


#endif // BATTLE_HPP_
