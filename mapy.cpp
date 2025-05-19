#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "place and move");

    sf::CircleShape unit(25);
    unit.setFillColor(sf::Color::Magenta);

    float unitX = -100; // off-screen start
    float unitY = -100;
    bool placed = false;
    bool moving = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // mouse click, go
            if (!placed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                unitX = event.mouseButton.x - unit.getRadius();
                unitY = event.mouseButton.y - unit.getRadius();
                unit.setPosition(unitX, unitY);
                placed = true;
                moving = true;
            }
        }

        // move horizontally
        if (moving) {
            unitX += 0.2f;
            if (unitX > window.getSize().x - unit.getRadius() * 2) {
                unitX = window.getSize().x - unit.getRadius() * 2;
                moving = false;
            }
            unit.setPosition(unitX, unitY);
        }

        window.clear(sf::Color(100, 200, 100));
        if (placed)
            window.draw(unit);
        window.display();
    }

    return 0;
}