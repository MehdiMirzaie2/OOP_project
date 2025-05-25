#include "ShooterUnit.hpp"

ShooterUnit::ShooterUnit()
    : HP(200), damage(100), speed(5), radius_of_attack(20), cost(4), fireInterval(0.6f)
{
    idleTexture.loadFromFile("gunmo1.png");
    moveTexture.loadFromFile("gunmo2.png");
    setTexture(idleTexture);
}

void ShooterUnit::update(float deltaTime) {
    (void)deltaTime; // Silence unused parameter warning if not used

    if (fireClock.getElapsedTime().asSeconds() >= fireInterval) {
        sf::CircleShape bullet(3.f);
        bullet.setFillColor(sf::Color::Red);
        bullet.setPosition(getPosition());
        bullets.push_back(bullet);
        fireClock.restart();
    }

    for (auto& bullet : bullets) {
        bullet.move(2.0f, 0.f);
    }

    // Remove bullets that are off-screen...
}

void ShooterUnit::draw(sf::RenderWindow& window) {
    window.draw(*this);
    for (const auto& bullet : bullets) {
        window.draw(bullet);
    }
}
