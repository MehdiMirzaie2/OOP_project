#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include "HP.hpp"
#include "elixer.hpp"

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
        swingSprite.setScale(0.2f, 0.2f);
    }

    void update() {
        if (active) {
            swingSprite.move(speed, 0.f);
            if (swingSprite.getPosition().x > 1200)
                active = false;
        }
    }
};

class Bullet {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool active;

    Bullet(float x, float y, sf::Vector2f target, float speed = 2.5f)
        : shape(6.0f), active(true)
    {
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(6.0f, 6.0f);
        shape.setPosition(x, y);

        sf::Vector2f dir = target - sf::Vector2f(x, y);
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0)
            dir /= len;
        velocity = dir * speed;
    }

    void update() {
        if (active) {
            shape.move(velocity);
            sf::Vector2f pos = shape.getPosition();
            if (pos.x < 0 || pos.x > 1200 || pos.y < 0 || pos.y > 800)
                active = false;
        }
    }
};

// Struct for each swordguy unit
struct SwordguyUnit {
    sf::Sprite sprite;
    float x, y;
    bool moving;
    HPBar hp;
    std::vector<Attack> attacks;
    bool swinging;
    sf::Clock swingClock;
    sf::Clock swingAnimClock;
    float swingInterval;
    float swingAnimDuration;
    float spriteWidth;

    SwordguyUnit(const sf::Texture& idle, const sf::Texture& swing, const sf::Texture& atk, float px, float py)
        : sprite(idle), x(px), y(py), moving(true), hp(200.0f, 50.0f, 7.0f, 70.0f),
          swinging(false), swingInterval(1.0f), swingAnimDuration(0.18f)
    {
        sprite.setScale(0.3f, 0.3f);
        sprite.setOrigin(idle.getSize().x / 2.0f, idle.getSize().y / 2.0f);
        sprite.setPosition(x, y);
        spriteWidth = idle.getSize().x * 0.3f;
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

    // Machine gun setup (for test, can be removed if not needed)
    sf::RectangleShape gun(sf::Vector2f(30, 12));
    gun.setFillColor(sf::Color(100, 100, 100));
    float gunX = 1150.0f, gunY = 400.0f;
    gun.setOrigin(15, 6);
    gun.setPosition(gunX, gunY);
    HPBar gunHP(600.0f, 60.0f, 8.0f, 30.0f);

    std::vector<Bullet> bullets;
    sf::Clock bulletClock;
    float bulletInterval = 0.12f;

    // Elixir setup
    Elixir elixir;
    // For testing, set elixir to 10 at start
    for (int i = 0; i < 10; ++i) elixir.update();

    // Font for elixir number
    sf::Font font;
    font.loadFromFile("KOMIKABG.ttf"); // Make sure arial.ttf is in your project directory

    // Elixir bar settings (bottom middle)
    const int elixirBarMax = 10; // Max elixir is 10
    const float elixirBarUnitWidth = 20.f; // Width per elixir unit
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

    // All swordguy units
    std::vector<SwordguyUnit> swordguys;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Deploy swordguy on left mouse click if enough elixir
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (elixir.getElixir() >= 2) {
                    swordguys.emplace_back(unitTextureIdle, unitTextureSwing, swingTexture, mousePos.x, mousePos.y);
                    elixir.decreaseElixir(2);
                }
            }
        }

        elixir.update();

        // Machine gun fires at all swordguys if alive
        if (gunHP.currentHP > 0 && bulletClock.getElapsedTime().asSeconds() >= bulletInterval) {
            for (auto& sg : swordguys) {
                bullets.emplace_back(gunX, gunY, sf::Vector2f(sg.x, sg.y));
            }
            bulletClock.restart();
        }

        // Update bullets
        for (auto& b : bullets)
            b.update();

        // Update all swordguys
        for (auto& sg : swordguys) {
            if (sg.moving) {
                sg.x += 0.2f;
                if (sg.x > window.getSize().x - sg.spriteWidth / 2.0f) {
                    sg.x = window.getSize().x - sg.spriteWidth / 2.0f;
                    sg.moving = false;
                }
                sg.sprite.setPosition(sg.x, sg.y);

                // auto swing
                if (sg.swingClock.getElapsedTime().asSeconds() >= sg.swingInterval) {
                    sg.attacks.emplace_back(sg.x + 30, sg.y, swingTexture);
                    sg.sprite.setTexture(unitTextureSwing);
                    sg.swinging = true;
                    sg.swingAnimClock.restart();
                    sg.swingClock.restart();
                }
            }

            // timing of swing animation
            if (sg.swinging && sg.swingAnimClock.getElapsedTime().asSeconds() >= sg.swingAnimDuration) {
                sg.sprite.setTexture(unitTextureIdle);
                sg.swinging = false;
            }

            for (auto& atk : sg.attacks)
                atk.update();

            // remove inactive swing
            sg.attacks.erase(
                std::remove_if(sg.attacks.begin(), sg.attacks.end(), [](const Attack& atk) { return !atk.active; }),
                sg.attacks.end()
            );
        }

        // Bullet hit swordguys
        for (auto& sg : swordguys) {
            sf::Vector2f unitPos(sg.x, sg.y);
            float unitRadius = sg.spriteWidth * 0.45f;
            for (auto& b : bullets) {
                if (!b.active) continue;
                sf::Vector2f bulletPos = b.shape.getPosition();
                float dist = std::sqrt((bulletPos.x - unitPos.x) * (bulletPos.x - unitPos.x) +
                                       (bulletPos.y - unitPos.y) * (bulletPos.y - unitPos.y));
                if (dist < unitRadius) {
                    b.active = false;
                    sg.hp.setHP(sg.hp.currentHP - 10.0f);
                }
            }
        }

        // Remove dead swordguys
        swordguys.erase(
            std::remove_if(swordguys.begin(), swordguys.end(), [](const SwordguyUnit& sg) { return sg.hp.currentHP <= 0; }),
            swordguys.end()
        );

        // Remove inactive bullets
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return !b.active; }),
            bullets.end()
        );

        // Swing attack machine gun
        if (gunHP.currentHP > 0) {
            sf::FloatRect gunBounds = gun.getGlobalBounds();
            for (auto& sg : swordguys) {
                for (auto& atk : sg.attacks) {
                    if (atk.active && atk.swingSprite.getGlobalBounds().intersects(gunBounds)) {
                        gunHP.setHP(gunHP.currentHP - 150.0f);
                        atk.active = false;
                    }
                }
            }
        }

        window.clear(sf::Color::Transparent);

        // Draw all swordguys and their HP bars/attacks
        for (auto& sg : swordguys) {
            if (sg.hp.currentHP > 0) {
                window.draw(sg.sprite);
                sg.hp.draw(window, sg.x, sg.y);
                for (const auto& atk : sg.attacks)
                    if (atk.active)
                        window.draw(atk.swingSprite);
            }
        }

        // Draw machine gun if alive
        if (gunHP.currentHP > 0) {
            window.draw(gun);
            gunHP.draw(window, gunX - 30.0f, gunY);
        }

        // Draw bullets if gun is alive
        if (gunHP.currentHP > 0) {
            for (const auto& b : bullets)
                if (b.active)
                    window.draw(b.shape);
        }

        // Draw elixir bar at bottom middle
        float elixirRatio = static_cast<float>(elixir.getElixir()) / elixirBarMax;
        elixirBarFront.setSize(sf::Vector2f(elixirBarWidth * elixirRatio, elixirBarHeight));
        window.draw(elixirBarBack);
        window.draw(elixirBarFront);

        // Draw elixir number to the left of the bar
        std::stringstream ss;
        ss << elixir.getElixir();
        sf::Text elixirText;
        elixirText.setFont(font);
        elixirText.setString(ss.str());
        elixirText.setCharacterSize(28);
        elixirText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = elixirText.getLocalBounds();
        elixirText.setOrigin(textRect.width, textRect.height / 2);
        elixirText.setPosition(elixirBarX - 10.f, elixirBarY + elixirBarHeight / 2 - 4);
        window.draw(elixirText);

        window.display();
    }

    return 0;
}