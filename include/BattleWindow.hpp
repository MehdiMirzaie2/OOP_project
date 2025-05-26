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
    Map gameMap;
    Director director;
    int m_turn;
    User user1; // bad design, must be passed from the game class, currently here for demo deployment
                // units that are spawned currently
    sf::Clock gameClock;

    User user2;
    int num_deployed[2] = {0, 0};

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
    void checkWinner();
};

#endif // BATTLE_HPP_
