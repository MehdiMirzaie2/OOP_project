#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

class HPBar {
public:
    float maxHP;
    float currentHP;
    float width;
    float height;
    float offsetY;
    sf::RectangleShape back;
    sf::RectangleShape bar;

    HPBar(float maxHP, float width, float height, float offsetY);
    void setColor(const sf::Color& color);
    void setHP(float hp);
    void draw(sf::RenderWindow& window, float x, float y);
};