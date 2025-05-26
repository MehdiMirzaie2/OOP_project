#pragma once
#include <SFML/Graphics.hpp>

class ElixirBar {
public:
    ElixirBar(int maxElixir, float unitWidth, float height);
    void update(int currentElixir);
    void draw(sf::RenderWindow& window, float x, float y);

private:
    int maxElixir;
    float unitWidth;
    float height;

    sf::RectangleShape back;
    sf::RectangleShape front;

    int currentElixirValue = 0; // Store for drawing

    sf::Font font; // Add this
    bool fontLoaded = false; // Track if font loaded
};