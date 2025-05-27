#ifndef STATSWINDOW_HPP_
#define STATSWINDOW_HPP_

#include "Window.hpp"

class StatsWindow
{
    private:
        sf::Sprite m_stats_bg;
        sf::Texture m_stats_bg_texture;
        
    public:
        int runWindow(std::string statfile);
}

#endif // STATSWINDOW_HPP_