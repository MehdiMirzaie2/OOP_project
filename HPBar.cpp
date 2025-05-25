#include "HPBar.hpp"
#include "Unit.hpp" // Add this line

HPBar::HPBar(float maxHP, float width, float height, float offsetY)
    : maxHP(maxHP), currentHP(maxHP), width(width), height(height), offsetY(offsetY)
{
    back.setSize(sf::Vector2f(width, height));
    back.setFillColor(sf::Color(50, 50, 50, 200));
    back.setOrigin(width, height / 2.0f);

    bar.setSize(sf::Vector2f(width, height));
    bar.setFillColor(sf::Color::Green);
    bar.setOrigin(width, height / 2.0f);
}

void HPBar::setColor(const sf::Color& color) {
    bar.setFillColor(color);
}

void HPBar::setHP(float hp) {
    currentHP = std::max(0.f, std::min(hp, maxHP));
}

void HPBar::draw(sf::RenderWindow& window, float x, float y) {
    float hpRatio = (maxHP > 0) ? (currentHP / maxHP) : 0.f;
    sf::Vector2f barPos(x + width / 2.0f, y - offsetY);
    back.setPosition(barPos);
    bar.setPosition(x + width, y - offsetY); // Position right edge above the unit
    bar.setSize(sf::Vector2f(width * hpRatio, height));
    bar.setOrigin(width, height / 2.0f); // Origin at right edge

    window.draw(back);
    window.draw(bar);
}