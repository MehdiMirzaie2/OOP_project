#ifndef DECK_HPP_
#define DECK_HPP_


#include "Unit.hpp"

const int MAX_UNITS = 5;

class Deck : public Drawable{
    private:
        sf::VertexArray rectangle;
        sf::VertexArray inner_recs;
        Unit** units; // pointer to pointers to units to allow polymorphism
        int current_no_units;
        bool* isPicked;

    public:
        Deck();

        bool* getIsPicked();
        void setIsPicked(int pick);
        Unit** getUnits();
        void addUnit(Unit* unit);
        void replaceUnit(Unit* unit, Unit* to_be_replaced);
        void draw(sf::RenderWindow* window);
        
};

#endif // DECK_HPP_