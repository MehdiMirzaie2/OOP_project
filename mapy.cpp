#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "mover circle");

    // texture 
    sf::Texture unitTexture;
    if (!unitTexture.loadFromFile("ranger2.png")) { // <-- image same folder
        return 1; // not found, exit
    }
    sf::Sprite unitSprite(unitTexture);
    unitSprite.setScale(0.2f, 0.2f); // scale to fit, adjust size
    unitSprite.setPosition(-100, -100); // start off screen, until mouse click

    float unitX = -100;
    float unitY = -100;
    bool placed = false;
    bool moving = false;

    // center origin
    sf::Vector2u texSize = unitTexture.getSize();
    float spriteWidth = texSize.x * 0.2f;
    unitSprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // mouse click put sprite
            if (!placed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                unitX = event.mouseButton.x;
                unitY = event.mouseButton.y;
                unitSprite.setPosition(unitX, unitY);
                placed = true;
                moving = true;
            }
        }

        // move horizontally
        if (moving) {
            unitX += 0.2f; // moving speed
            if (unitX > window.getSize().x - spriteWidth / 2.0f) {
                unitX = window.getSize().x - spriteWidth / 2.0f;
                moving = false;
            }
            unitSprite.setPosition(unitX, unitY);
        }

        window.clear(sf::Color(100, 200, 100));
        if (placed)
            window.draw(unitSprite);
        window.display();
    }

    return 0;
}