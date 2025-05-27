#ifndef STATSWINDOW_HPP_
#define STATSWINDOW_HPP_

#include "Window.hpp" 
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>   
#include <sstream>   
#include <iostream>  

#define STATS_WINDOW_BACK 0 // Signal to return to main menu

class StatsWindow : public Window
{
private:
    sf::Sprite m_stats_bg_sprite;
    sf::Texture m_stats_bg_texture;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_player1StatsText;
    sf::Text m_player2StatsText;
    sf::Text m_backButtonText;

    // Helper to load stats from file and update text objects
    void loadStats(const std::string& filename);
    // Helper to set up text properties
    void setupText(sf::Text& textObject, const std::string& content, int charSize, sf::Color color, float x, float y);

public:
    StatsWindow(); 
    int runWindow(const std::string& statfile);
    int runWindow() override {
        std::cerr << "Warning: Parameterless StatsWindow::runWindow() called. Use runWindow(statfile) instead." << std::endl;
        return -1; 
    }
};

#endif // STATSWINDOW_HPP_
