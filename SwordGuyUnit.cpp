#include "SwordGuyUnit.hpp"

SwordGuyUnit::SwordGuyUnit()
    : HP(400), damage(120), speed(3), radius_of_attack(15), cost(2), swingInterval(1.0f)
{
    idleTexture.loadFromFile("swordm1.png");
    swingTexture.loadFromFile("swordm2.png");
    slashTexture.loadFromFile("swordslash.png");
    setTexture(idleTexture);
}


void SwordGuyUnit::update(float deltaTime) {
    (void)deltaTime; // Silence unused parameter warning if not used

    if (swingClock.getElapsedTime().asSeconds() >= swingInterval) {
        sf::Sprite slash(slashTexture);
        slash.setPosition(getPosition().x + 30, getPosition().y);
        slashes.push_back(slash);
        setTexture(swingTexture);
        swingClock.restart();
    }

    for (auto& slash : slashes) {
        slash.move(0.6f, 0.f);
    }

    // Remove slashes that are off-screen
    slashes.erase(
        std::remove_if(slashes.begin(), slashes.end(), [](const sf::Sprite& slash) {
            return slash.getPosition().x > 1200;
        }),
        slashes.end()
    );
}

void SwordGuyUnit::draw(sf::RenderWindow& window) {
    window.draw(static_cast<sf::Sprite&>(*this));
    for (const auto& slash : slashes) {
        window.draw(slash);
    }
}