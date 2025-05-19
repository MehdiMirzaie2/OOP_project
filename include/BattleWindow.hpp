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
	int m_turn;
        User user1; // bad design, must be passed from the game class, currently here for demo deployment

	User user2;
	int num_deployed[2] = {0, 0};

	void loadDecks();
	void deploye(sf::Event);

    public:
        BattleWindow();
        void draw_all(sf::RenderWindow* window);
        int runWindow();
};


#endif // BATTLE_HPP_
