#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath> // distance calc


class Attack {
public:
    sf::Sprite swingSprite;
    float speed;
    bool active;

    Attack(float x, float y, const sf::Texture& texture, float speed = 0.6f)
        : swingSprite(texture), speed(speed), active(true)
    {
        swingSprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        swingSprite.setPosition(x, y);
        swingSprite.setScale(0.2f, 0.2f); // adjust as needed
    }

    void update() {
        if (active) {
            swingSprite.move(speed, 0.f);
            if (swingSprite.getPosition().x > 1200)
                active = false;
        }
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "swordguy");

    // swordguy textures
    sf::Texture unitTextureIdle;
    if (!unitTextureIdle.loadFromFile("swordm1.png")) {
        return 1;
    }
    sf::Texture unitTextureSwing;
    if (!unitTextureSwing.loadFromFile("swordm2.png")) {
        return 1;
    }
    sf::Texture swingTexture;
    if (!swingTexture.loadFromFile("swordslash.png")) {
        return 1;
    }

    sf::Sprite unitSprite(unitTextureIdle);
    unitSprite.setScale(0.3f, 0.3f);
    unitSprite.setPosition(-100, -100);

    float unitX = -100;
    float unitY = -100;
    bool placed = false;
    bool moving = false;

    sf::Vector2u texSize = unitTextureIdle.getSize();
    float spriteWidth = texSize.x * 0.3f;
    unitSprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);

    std::vector<Attack> attacks;

    sf::Clock swingClock;
    float swingInterval = 1.0f;

    // swing animation
    bool swinging = false;
    sf::Clock swingAnimClock;
    float swingAnimDuration = 0.18f; // seconds to show swing frame

    // health bar set up
    float maxHP = 200.0f;
    float currentHP = maxHP;
    float healthBarWidth = 50.0f;
    float healthBarHeight = 7.0f;
    float healthBarOffsetY = 70.0f; // distance above the unit

    sf::RectangleShape healthBarBack(sf::Vector2f(healthBarWidth, healthBarHeight));
    healthBarBack.setFillColor(sf::Color(50, 50, 50, 180));
    healthBarBack.setOrigin(healthBarWidth / 2.0f, healthBarHeight / 2.0f);

    sf::RectangleShape healthBar(sf::Vector2f(healthBarWidth, healthBarHeight));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setOrigin(healthBarWidth / 2.0f, healthBarHeight / 2.0f);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!placed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                unitX = event.mouseButton.x;
                unitY = event.mouseButton.y;
                unitSprite.setPosition(unitX, unitY);
                placed = true;
                moving = true;
                swingClock.restart();
            }
        }

      

        if (moving) {
            unitX += 0.2f;
            if (unitX > window.getSize().x - spriteWidth / 2.0f) {
                unitX = window.getSize().x - spriteWidth / 2.0f;
                moving = false;
            }
            unitSprite.setPosition(unitX, unitY);

            // auto swing
            if (swingClock.getElapsedTime().asSeconds() >= swingInterval) {
                attacks.emplace_back(unitX + 30, unitY, swingTexture);
                unitSprite.setTexture(unitTextureSwing); // show swing frame
                swinging = true;
                swingAnimClock.restart();
                swingClock.restart();
            }
        }

        // timing of swing animation
        if (swinging && swingAnimClock.getElapsedTime().asSeconds() >= swingAnimDuration) {
            unitSprite.setTexture(unitTextureIdle); // back to idle
            swinging = false;
        }

        for (auto& atk : attacks)
            atk.update();

        // remove inactive 
        attacks.erase(
            std::remove_if(attacks.begin(), attacks.end(), [](const Attack& atk) { return !atk.active; }),
            attacks.end()
        );


        window.clear(sf::Color::Transparent);
        if (placed && currentHP > 0) {
            window.draw(unitSprite);


            // update health bar position and size
            sf::Vector2f barPos(unitX, unitY - healthBarOffsetY);
            healthBarBack.setPosition(barPos);
            healthBar.setPosition(barPos);

            float hpRatio = currentHP / maxHP;
            // right-to-left reduction
            healthBar.setOrigin(healthBarWidth / 2.0f, healthBarHeight / 2.0f);
            healthBarBack.setOrigin(healthBarWidth / 2.0f, healthBarHeight / 2.0f);
            // right edge stays fixed
            healthBar.setPosition(unitX + healthBarWidth / 2.0f, unitY - healthBarOffsetY);
            healthBarBack.setPosition(unitX + healthBarWidth / 2.0f, unitY - healthBarOffsetY);
            healthBar.setSize(sf::Vector2f(healthBarWidth * hpRatio, healthBarHeight));

            window.draw(healthBarBack);
            window.draw(healthBar);

            // create swing attacks only if unit is alive
            for (const auto& atk : attacks)
                if (atk.active)
                    window.draw(atk.swingSprite);
        }

        

        window.display();
    }

    return 0;
}