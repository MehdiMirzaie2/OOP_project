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
    float hpRatio = currentHP / maxHP;

    if (hpRatio > 0.66f) bar.setFillColor(sf::Color::Green);
    else if (hpRatio > 0.33f) bar.setFillColor(sf::Color::Yellow);
    else bar.setFillColor(sf::Color::Red);
}

void HPBar::draw(sf::RenderWindow& window, float x, float y) {
    float hpRatio = (maxHP > 0) ? (currentHP / maxHP) : 0.f;
    sf::Vector2f barPos(x, y - offsetY); // position directly above the unit
    back.setPosition(barPos);
    bar.setPosition(barPos);
    bar.setSize(sf::Vector2f(width * hpRatio, height));
    bar.setOrigin(width / 2.0f, height / 2.0f);
    back.setOrigin(width / 2.0f, height / 2.0f);

    window.draw(back);
    window.draw(bar);
}