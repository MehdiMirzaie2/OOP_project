#ifndef BATTLEWINDOW_HPP_
#define BATTLEWINDOW_HPP_

#include "Window.hpp"
#include "map.hpp"
#include "Director.hpp"
#include "User.hpp"
#include "Unit.hpp"
#include "ElixirBar.hpp"

class BattleWindow : public Window {
private:
    Map gameMap;
    Director director;
    int m_turn;
    User user1, user2;  // Users holding game logic and elixir
    std::vector<Unit*> active_units;
    std::vector<Unit*> user1_units;
    std::vector<Unit*> user2_units;
    int num_deployed[2] = {0, 0};
    sf::Clock gameClock;

    // Initialize ElixirBars with maxElixir=8, unitWidth=20.f, height=30.f
    ElixirBar elixirBar1{8, 20.f, 30.f};
    ElixirBar elixirBar2{8, 20.f, 30.f};

    void loadDecks();
    void deploye(sf::Event);
    void selectUnit(sf::Event);

    // New private helper methods for elixir bars
    void updateElixirBars();
    void drawElixirBars(sf::RenderWindow& window);

public:
    BattleWindow();
    int runWindow();
    void checkCollisions();
    void updateUnits(sf::Time time_passed);
    void updateAttacks();

    // Override base class draw method or add one to draw UI
    void draw(sf::RenderWindow& window);
};

#endif // BATTLEWINDOW_HPP_