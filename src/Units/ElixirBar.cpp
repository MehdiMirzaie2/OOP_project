#include "ElixirBar.hpp"
#include "Elixir.hpp"
#include <iostream>

ElixirBar::ElixirBar(int maxElixir_, float unitWidth_, float height_)
    : maxElixir(maxElixir_), unitWidth(unitWidth_), height(height_) {

    back.setFillColor(sf::Color(60, 60, 60));
    front.setFillColor(sf::Color(180, 0, 255));  // Purple

    // Try to load font once
    fontLoaded = font.loadFromFile("KOMIKABG.ttf");

    if (!fontLoaded) {
    std::cerr << "Warning: Failed to load font KOMIKABG.ttf\n";
}
}

void ElixirBar::update(int currentElixir) {
    currentElixirValue = currentElixir; // Store for drawing
    float ratio = static_cast<float>(currentElixir) / maxElixir;
    float width = unitWidth * maxElixir;

    front.setSize(sf::Vector2f(width * ratio, height));
    back.setSize(sf::Vector2f(unitWidth * 8, height)); // Always 8-unit background
}

void ElixirBar::draw(sf::RenderWindow& window, float x, float y) {
    back.setPosition(x, y);
    front.setPosition(x, y);
    window.draw(back);
    window.draw(front);

    // Draw elixir value to the right of the bar
    if (fontLoaded) {
        sf::Text elixirText;
        elixirText.setFont(font);
        elixirText.setString(std::to_string(currentElixirValue));
        elixirText.setCharacterSize(static_cast<unsigned int>(height * 0.8f));
        elixirText.setFillColor(sf::Color::White);

        // Position: right of the bar, vertically centered
        float barWidth = unitWidth * maxElixir;
        sf::FloatRect textBounds = elixirText.getLocalBounds();
        elixirText.setOrigin(0, textBounds.top + textBounds.height / 2.f);
        elixirText.setPosition(x + barWidth + 10.f, y + height / 2.f);
        window.draw(elixirText);
    }
}