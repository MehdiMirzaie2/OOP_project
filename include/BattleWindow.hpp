#ifndef BATTLEWINDOW_HPP_
#define BATTLEWINDOW_HPP_

#include "Window.hpp"

class BattleWindow : public Window
// Renders the battle visuals like the map.
{
    private:
        Map gameMap;
    public:
        void runWindow();
};


#endif // BATTLE_HPP_