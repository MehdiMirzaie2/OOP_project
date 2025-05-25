#include "Deck.hpp"
#include <iostream>

Deck::Deck() : current_no_units(0) {
    for (int i = 0; i < MAX_UNITS; ++i) {
        Unit* new_unit = director.buildSwords();
        if (new_unit) {
            standardizeUnitAppearance(new_unit, i);
            units.push_back(new_unit);
        } else {
            std::cerr << "Failed to build unit\n";
        }
    }
    initGraphics();
}

Deck::Deck(int left_or_right) : current_no_units(0) {
    for (int i = 0; i < MAX_UNITS; ++i) {
        Unit* new_unit = director.buildSwords();
        if (new_unit) {
            standardizeUnitAppearance(new_unit, i);
            units.push_back(new_unit);
        } else {
            std::cerr << "Failed to build unit\n";
        }
    }
    initGraphics();
}


// Setup deck background and unit slots
void Deck::initGraphics() {
    const float outerRectWidth = 600.f;
    const float outerRectHeight = 190.f;
    sf::Vector2u windowSize(1280, 720);

    sf::Vector2f outerTL(windowSize.x / 2.f - outerRectWidth / 2.f, windowSize.y - outerRectHeight - 10.f);

    // Deck background (TriangleStrip)
    rectangle.setPrimitiveType(sf::TriangleStrip);
    rectangle.resize(4);
    rectangle[0].position = outerTL;
    rectangle[1].position = outerTL + sf::Vector2f(0, outerRectHeight);
    rectangle[2].position = outerTL + sf::Vector2f(outerRectWidth, 0);
    rectangle[3].position = outerTL + sf::Vector2f(outerRectWidth, outerRectHeight);
    for (int i = 0; i < 4; ++i)
        rectangle[i].color = sf::Color(50, 50, 50, 200); // dark semi-transparent gray

    // Unit slots (Triangles)
    const int vpr = 6;
    float innerW = 70.f;
    float innerH = 100.f;
    float spacing = 10.f;
    float pad_x = 20.f;
    float pad_y = 20.f;
    sf::Vector2f innerStart = outerTL + sf::Vector2f(pad_x, pad_y);

    inner_recs.setPrimitiveType(sf::Triangles);
    inner_recs.resize(vpr * MAX_UNITS);

    for (int i = 0; i < MAX_UNITS; ++i) {
        int start = i * vpr;
        sf::Vector2f tl = innerStart + sf::Vector2f(i * (innerW + spacing), 0);
        sf::Vector2f tr = tl + sf::Vector2f(innerW, 0);
        sf::Vector2f bl = tl + sf::Vector2f(0, innerH);
        sf::Vector2f br = tl + sf::Vector2f(innerW, innerH);

        inner_recs[start + 0].position = tl;
        inner_recs[start + 1].position = bl;
        inner_recs[start + 2].position = tr;
        inner_recs[start + 3].position = tr;
        inner_recs[start + 4].position = bl;
        inner_recs[start + 5].position = br;

        for (int j = 0; j < vpr; ++j)
            inner_recs[start + j].color = sf::Color::Red;
    }
}

// Align + scale a unit to slot i
void Deck::standardizeUnitAppearance(Unit* unit, int index) {
    const float innerW = 70.f;
    const float innerH = 100.f;
    const float spacing = 10.f;
    const float pad_x = 20.f;
    const float pad_y = 20.f;
    sf::Vector2u windowSize(1280, 720);
    float outerRectWidth = 600.f;
    float outerRectHeight = 190.f;
    sf::Vector2f outerTL(windowSize.x / 2.f - outerRectWidth / 2.f, windowSize.y - outerRectHeight - 10.f);

    sf::Vector2f basePos = outerTL + sf::Vector2f(pad_x + index * (innerW + spacing), pad_y);

    // Center unit inside slot
    basePos += sf::Vector2f((innerW - 64) / 2.f, (innerH - 64) / 2.f);
    unit->setLocation(sf::Vector2i(basePos));

    // Scale to uniform size (64x64)
    sf::FloatRect bounds = unit->getSprite().getLocalBounds();
    if (bounds.width > 0 && bounds.height > 0) {
        unit->getSprite().setScale(64.f / bounds.width, 64.f / bounds.height);
    }
}

void Deck::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
    window.draw(inner_recs);
    for (auto unit : units) {
        unit->draw(window);
    }
}

std::vector<Unit*> Deck::getUnits() {
    return units;
}

void Deck::addUnit(Unit* unit) {
    if (current_no_units < MAX_UNITS) {
        standardizeUnitAppearance(unit, current_no_units);
        units.push_back(unit);
        current_no_units++;
        std::cout << "Unit added successfully\n";
    } else {
        std::cout << "List full, please replace a unit to continue\n";
    }
}

void Deck::replaceUnit(Unit* unit, Unit* to_be_replaced) {
    for (int i = 0; i < current_no_units; ++i) {
        if (units[i] == to_be_replaced) {
            units[i] = unit;
            standardizeUnitAppearance(unit, i);
            std::cout << "Unit successfully found and replaced\n";
            return;
        }
    }
    std::cout << "Unit to be replaced not found\n";
}

Unit* Deck::getPickedUnit() {
    for (auto unit : units) {
        if (unit->getIsPicked())
            return unit;
    }
    return nullptr;
}
