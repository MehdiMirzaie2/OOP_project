#include <SFML/Graphics.hpp>
#include <sstream>
#include "elixer.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "Elixir Animation");

    // Elixir bar settings (bottom middle, like test file)
    const int elixirBarMax = 10;
    const float elixirBarUnitWidth = 20.f;
    const float elixirBarWidth = elixirBarUnitWidth * elixirBarMax;
    const float elixirBarHeight = 30.f;
    const float elixirBarX = (window.getSize().x - elixirBarWidth) / 2.f;
    const float elixirBarY = window.getSize().y - elixirBarHeight - 40.f;

    sf::RectangleShape elixirBarBack(sf::Vector2f(elixirBarWidth, elixirBarHeight));
    elixirBarBack.setFillColor(sf::Color(60, 60, 60));
    elixirBarBack.setPosition(elixirBarX, elixirBarY);

    sf::RectangleShape elixirBarFront(sf::Vector2f(elixirBarWidth, elixirBarHeight));
    elixirBarFront.setFillColor(sf::Color(180, 0, 255));
    elixirBarFront.setPosition(elixirBarX, elixirBarY);

    // Font for elixir number
    sf::Font font;
    font.loadFromFile("KOMIKABG.ttf"); // Make sure the font file is present

    Elixir elixir;
    // For testing, set elixir to 10 at start
    for (int i = 0; i < 10; ++i) elixir.update();

    // For demo: animate elixir increasing from 0 to max, then reset
    elixir = Elixir(); // Reset elixir to 0 at start

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        elixir.update();

        // Demo animation: increase elixir automatically
        static sf::Clock animClock;
        if (animClock.getElapsedTime().asSeconds() > 0.05f) {
            if (elixir.getElixir() < elixirBarMax) {
                elixir.update();
            } else {
                // Reset to 0 to loop the animation
                elixir = Elixir();
            }
            animClock.restart();
        }

        // Always match the background to the full bar size and position
        elixirBarBack.setSize(sf::Vector2f(elixirBarWidth, elixirBarHeight));
        elixirBarBack.setPosition(elixirBarX, elixirBarY);

        // Foreground (purple) bar matches current elixir
        float elixirRatio = static_cast<float>(elixir.getElixir()) / elixirBarMax;
        float currentBarWidth = elixirBarWidth * elixirRatio;

        // Background always shows 8 elixir units in length
        float backgroundBarWidth = elixirBarUnitWidth * 8;
        elixirBarBack.setSize(sf::Vector2f(backgroundBarWidth, elixirBarHeight));
        elixirBarBack.setPosition(elixirBarX, elixirBarY);

        elixirBarFront.setSize(sf::Vector2f(currentBarWidth, elixirBarHeight));
        elixirBarFront.setPosition(elixirBarX, elixirBarY);

        window.clear(sf::Color::Transparent);
        window.draw(elixirBarBack);
        window.draw(elixirBarFront);

        // Draw elixir number to the left of the bar, right-aligned
        std::stringstream ss;
        ss << elixir.getElixir();
        sf::Text elixirText;
        elixirText.setFont(font);
        elixirText.setString(ss.str());
        elixirText.setCharacterSize(28);
        elixirText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = elixirText.getLocalBounds();
        elixirText.setOrigin(textRect.width, textRect.height / 2); // Right-align
        elixirText.setPosition(elixirBarX - 10.f, elixirBarY + elixirBarHeight / 2 - 4);
        window.draw(elixirText);

        window.display();
    }

    return 0;
}