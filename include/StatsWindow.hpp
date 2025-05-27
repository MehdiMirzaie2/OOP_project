#ifndef STATSWINDOW_HPP_
#define STATSWINDOW_HPP_

#include "Window.hpp" // Provides sf::RenderWindow m_window and constants
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>   // For file operations
#include <sstream>   // For string stream operations
#include <iostream>  // For cerr (error output)

// Define a return code for the back button
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
    StatsWindow(); // Constructor to load resources like font and textures

    // runWindow specifically for Stats, takes statfile path
    // This doesn't override Window::runWindow() if that one is parameterless.
    // This is a distinct method called by the Game class.
    int runWindow(const std::string& statfile);

    // If Window.hpp's runWindow is `virtual int runWindow() = 0;`
    // and you intend to override it, StatsWindow would need a parameterless runWindow.
    // However, the request implies passing statfile, so we'll keep it this way.
    // The Game class will call this specific version.
    // To satisfy the pure virtual function from Window base class, if it exists and is parameterless:
    virtual int runWindow() override {
    // This version could call the parameterized one with a default file,
    // or indicate it's not meant to be called directly.
    std::cerr << "Warning: Parameterless StatsWindow::runWindow() called. Use runWindow(statfile) instead." << std::endl;
    // For now, let's assume Game.cpp calls the version with statfile.
    // If a default stats file is known, it could be used here.
    // For example: return runWindow("stats.txt");
    return -1; // Indicate an issue or improper call
    }
};

#endif // STATSWINDOW_HPP_
