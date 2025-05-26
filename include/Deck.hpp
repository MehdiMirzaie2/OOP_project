#ifndef DECK_HPP_
#define DECK_HPP_

#include "Unit.hpp"
#include <vector>
#include "Director.hpp"
const int MAX_UNITS = 5;

class Deck : public Drawable
{
private:
    sf::VertexArray rectangle;
    sf::VertexArray inner_recs;
    Director director;
    std::vector<std::shared_ptr<Unit>> units;

public:
    Deck();
    Deck(int);

    std::vector<std::shared_ptr<Unit>> &getUnits();
    void draw(sf::RenderWindow *window);
    std::shared_ptr<Unit> getPickedUnit();
    void swapDeployedUnit(const std::shared_ptr<Unit> &unit);
};

#endif // DECK_HPP_
