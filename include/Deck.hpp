#ifndef DECK_HPP_
#define DECK_HPP_

#include "Unit.hpp"
#include <vector>
#include "Director.hpp"

const int MAX_UNITS = 5;

class Deck
{
private:
    Director m_director;
    std::set<std::shared_ptr<Unit>> m_units;

public:
    Deck(); // Default constructor
    Deck(int); // Constructor that initializes the deck with an alliance

    std::shared_ptr<Unit> generateTowers(int alliance); // Creates and returns Tower units for the specified alliance
    std::set<std::shared_ptr<Unit>> &getUnits(); // Returns a reference to the set of units in the deck
    void draw(sf::RenderWindow *window); // Draws all units in the deck to the window
    std::shared_ptr<Unit> getPickedUnit(); // Returns the currently picked unit (if any)
    void swapDeployedUnit(const std::shared_ptr<Unit> &unit); // Replaces a deployed unit with another
};

#endif // DECK_HPP_
