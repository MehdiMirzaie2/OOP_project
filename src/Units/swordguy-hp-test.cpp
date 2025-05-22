#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath> // distant calc


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

class Bullet {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool active;

    // bullet speed
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

    // health bar
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

    
    // Machine gun setup (to test the stuff)  and HP bar
    sf::RectangleShape gun(sf::Vector2f(30, 12));
    gun.setFillColor(sf::Color(100, 100, 100));
    float gunX = 1150.0f, gunY = 400.0f;
    gun.setOrigin(15, 6);
    gun.setPosition(gunX, gunY);

    // machine gun HP bar
    float gunMaxHP = 600.0f;
    float gunCurrentHP = gunMaxHP;
    float gunBarWidth = 60.0f;
    float gunBarHeight = 8.0f;
    float gunBarOffsetY = 30.0f; // above the gun

    sf::RectangleShape gunBarBack(sf::Vector2f(gunBarWidth, gunBarHeight));
    gunBarBack.setFillColor(sf::Color(50, 50, 50, 180));
    gunBarBack.setOrigin(gunBarWidth / 2.0f, gunBarHeight / 2.0f);

    sf::RectangleShape gunBar(sf::Vector2f(gunBarWidth, gunBarHeight));
    gunBar.setFillColor(sf::Color::Red);
    gunBar.setOrigin(gunBarWidth / 2.0f, gunBarHeight / 2.0f);

    std::vector<Bullet> bullets;
    sf::Clock bulletClock;
    float bulletInterval = 0.12f; // machine gun fire rate

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

        // gun fires at the unit if placed and gun is alive
        if (placed && gunCurrentHP > 0 && bulletClock.getElapsedTime().asSeconds() >= bulletInterval) {
            bullets.emplace_back(gunX, gunY, sf::Vector2f(unitX, unitY));
            bulletClock.restart();
        }

        // udate bullets
        for (auto& b : bullets)
            b.update();

        // bullet hit unit
        if (placed) {
            sf::Vector2f unitPos(unitX, unitY);
            float unitRadius = spriteWidth * 0.45f; // approximate collision radius

            for (auto& b : bullets) {
                if (!b.active) continue;
                sf::Vector2f bulletPos = b.shape.getPosition();
                float dist = std::sqrt((bulletPos.x - unitPos.x) * (bulletPos.x - unitPos.x) +
                                       (bulletPos.y - unitPos.y) * (bulletPos.y - unitPos.y));
                if (dist < unitRadius) {
                    b.active = false;
                    currentHP -= 2.0f; // damage control of the bullet
                    if (currentHP < 0) currentHP = 0;
                }
            }
        }

        // remove inactive bulle
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return !b.active; }),
            bullets.end()
        );

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

        // remove inactive swing
        attacks.erase(
            std::remove_if(attacks.begin(), attacks.end(), [](const Attack& atk) { return !atk.active; }),
            attacks.end()
        );

        // swing attack machine gun 
        // eachswing attack hit gun does 150hp damage (testing with gun having 600hp)
        if (placed && gunCurrentHP > 0) {
            sf::FloatRect gunBounds = gun.getGlobalBounds();
            for (auto& atk : attacks) {
                if (atk.active && atk.swingSprite.getGlobalBounds().intersects(gunBounds)) {
                    gunCurrentHP -= 150.0f;
                    if (gunCurrentHP < 0) gunCurrentHP = 0;
                    atk.active = false; // deactivate swing after hit
                }
            }
        }

        window.clear(sf::Color::Transparent);
        if (placed && currentHP > 0) {
            window.draw(unitSprite);

            // draw machine gun if alive
            if (gunCurrentHP > 0) {
                window.draw(gun);

                // draw hp over gun
                sf::Vector2f gunBarPos(gunX, gunY - gunBarOffsetY);
                gunBarBack.setPosition(gunBarPos);
                gunBar.setPosition(gunBarPos);

                float gunHpRatio = gunCurrentHP / gunMaxHP;
                // right-to-left reduction for hp bar

                gunBar.setOrigin(gunBarWidth / 2.0f, gunBarHeight / 2.0f);
                gunBarBack.setOrigin(gunBarWidth / 2.0f, gunBarHeight / 2.0f);

                // position bar so right edge stays fixed
                gunBar.setPosition(gunX + gunBarWidth / 2.0f - 30.0f, gunY - gunBarOffsetY);
                gunBarBack.setPosition(gunX + gunBarWidth / 2.0f - 30.0f, gunY - gunBarOffsetY);
                gunBar.setSize(sf::Vector2f(gunBarWidth * gunHpRatio, gunBarHeight));

                window.draw(gunBarBack);
                window.draw(gunBar);
            }

            // update health bar position and size 
            sf::Vector2f barPos(unitX, unitY - healthBarOffsetY);
            healthBarBack.setPosition(barPos);
            healthBar.setPosition(barPos);

            float hpRatio = currentHP / maxHP;

            // set origin to right edge for right-to-left reduction
            healthBar.setOrigin(healthBarWidth / 2.0f, healthBarHeight / 2.0f);
            healthBarBack.setOrigin(healthBarWidth / 2.0f, healthBarHeight / 2.0f);

            // position bar so right edge stays fixed
            healthBar.setPosition(unitX + healthBarWidth / 2.0f, unitY - healthBarOffsetY);
            healthBarBack.setPosition(unitX + healthBarWidth / 2.0f, unitY - healthBarOffsetY);
            healthBar.setSize(sf::Vector2f(healthBarWidth * hpRatio, healthBarHeight));

            window.draw(healthBarBack);
            window.draw(healthBar);

            // draw swing attacks only if unit is alive
            for (const auto& atk : attacks)
                if (atk.active)
                    window.draw(atk.swingSprite);
        }

        // draw bullets only if gun is alive
        if (gunCurrentHP > 0) {
            for (const auto& b : bullets)
                if (b.active)
                    window.draw(b.shape);
        }

        window.display();
    }

    return 0;
}