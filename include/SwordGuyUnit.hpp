#pragma once
#include <SFML/Graphics.hpp>
#include "Unit.hpp"
#include <vector>

class SwordGuyUnit : public sf::Sprite {
public:
    SwordGuyUnit();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setCustomization(const std::string& customization);

    int HP;
    int damage;
    int speed;
    int radius_of_attack;
    int cost;

private:
    float swingInterval;
    sf::Clock swingClock;
    std::vector<sf::Sprite> slashes;
    sf::Texture idleTexture;
    sf::Texture swingTexture;
    sf::Texture slashTexture;
};
