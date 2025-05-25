#ifndef DECK_HPP_
#define DECK_HPP_

#include "Unit.hpp"
#include <vector>
#include "Director.hpp"
#include <SFML/Graphics.hpp>

const int MAX_UNITS = 5;

class Deck : public Drawable {
private:
    sf::VertexArray rectangle;      // Deck background
    sf::VertexArray inner_recs;     // Unit slots
    Director director;
    std::vector<Unit*> units;
    int current_no_units;

    void initGraphics(); // Sets up rectangles
    void standardizeUnitAppearance(Unit* unit, int index); // Align + scale units

public:
    Deck(); // Left-side default
    Deck(int side); // 0 = left, 1 = right

    std::vector<Unit*> getUnits();
    void addUnit(Unit* unit);
    void replaceUnit(Unit* unit, Unit* to_be_replaced);
    Unit* getPickedUnit();
    void draw(sf::RenderWindow& window);
    Unit* getPickedUnit();
    void addUnit(Unit* unit);
    void replaceUnit(Unit* unit, Unit* to_be_replaced);
};

#endif // DECK_HPP_
