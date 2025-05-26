#ifndef DECK_HPP_
#define DECK_HPP_


#include "Unit.hpp"
#include <vector>
#include "Director.hpp"
const int MAX_UNITS = 5;

class Deck : public Drawable{
    private:
        sf::VertexArray rectangle;
        sf::VertexArray inner_recs;

	Director director;
	std::vector<std::shared_ptr<Unit>> units;
	//Unit** units; 
        int current_no_units;
        //bool* isPicked;

    public:
        Deck();
        Deck(int);
        Unit* generateKing(int alliance);
        Unit* generateTowers(int alliance);
        //bool* getIsPicked();
        //void setIsPicked(int pick);
        std::vector<std::shared_ptr<Unit>>& getUnits();
        // void addUnit(Unit* unit);
        // void replaceUnit(Unit* unit, Unit* to_be_replaced);
        void draw(sf::RenderWindow* window);
       	Unit *getPickedUnit(); 
};

#endif // DECK_HPP_
