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
    User m_user1; 
    User m_user2;
    sf::Clock m_gameClock;

    void deploye(sf::Event);
    void selectUnit(sf::Event);

public:
    BattleWindow();
    void draw_all(sf::RenderWindow *window);
    int runWindow();
    void checkCollisions();
    void updateUnits();
    void updateAttacks();
    void startUnitAttack(Unit *attacker);
};

#endif // BATTLE_HPP_
