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

	User user2;
	int num_deployed[2] = {0, 0};

	std::vector<Unit *> user1_units;
	std::vector<Unit *> user2_units;
	void loadDecks();
	void deploye(sf::Event);
	void selectUnit(sf::Event);
//void deploy(int index, sf::Vector2i d_loc);

    public:
        BattleWindow();
        void draw_all(sf::RenderWindow* window);
        int runWindow();
};


#endif // BATTLE_HPP_
