#ifndef BATTLEWINDOW_HPP_
#define BATTLEWINDOW_HPP_

#include "Window.hpp"
#include "map.hpp"
#include "Director.hpp"
#include "User.hpp"

class BattleWindow : public Window
// Renders the battle visuals like the map.
{
    private:
        Map gameMap;
        Director director;
        User user1; // bad design, must be passed from the game class, currently here for demo deployment
        std::vector <Unit*> active_units; // units that are spawned currently
        sf::Clock gameClock;
       
    public:
        BattleWindow();
        void draw_all(sf::RenderWindow* window);
        int runWindow();
        void checkCollisions();
        void updateUnits(sf::Time time_passed);
        void updateAttacks();
        void startUnitAttacks(Unit* attacker);
};


#endif // BATTLE_HPP_