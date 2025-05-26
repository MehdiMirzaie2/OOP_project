#include "../../include/Deck.hpp"

Deck::Deck(int left_or_right)
{
	current_no_units = 0;
	//isPicked = false;

	int left_pos;
    int alliance;
    if (left_or_right == 0)
    {
        left_pos = 50;
        alliance = 0;
    }
    else{
        left_pos = 1090;
        alliance = 1;
    }
    std::vector<Unit*> initialized_units;
    Unit *u1 = director.buildSwords(alliance);
    Unit *u2 = director.buildMage(alliance);
    Unit *u3 = director.buildShooter(alliance);
    Unit *u4 = director.buildTank(alliance);
    Unit *u5 = director.buildSwords(alliance);
    initialized_units.push_back(u1);
    initialized_units.push_back(u2);
    initialized_units.push_back(u3);
    initialized_units.push_back(u4);
    initialized_units.push_back(u5);


    for(long unsigned int i = 0; i < initialized_units.size(); i++){
        if (initialized_units[i]) {
			std::cout << "pushing unit\n";
			sf::Vector2f location(left_pos, (50 * i) + 100);
			initialized_units[i]->setLocation(location);
			initialized_units[i]->setDeckPosition(location);
			units.push_back(std::shared_ptr<Unit> (initialized_units[i])); 
		}
		else
			std::cerr << "failed to build unit\n";
    }

	std::cout << "built deck\n";
}

Deck::Deck()
{
	current_no_units = 0;
	//isPicked = false;
    int alliance = 1;
    std::vector<Unit*> initialized_units;
    Unit *u1 = director.buildSwords(alliance);
    Unit *u2 = director.buildMage(alliance);
    Unit *u3 = director.buildShooter(alliance);
    Unit *u4 = director.buildTank(alliance);
    Unit *u5 = director.buildSwords(alliance);
    initialized_units.push_back(u1);
    initialized_units.push_back(u2);
    initialized_units.push_back(u3);
    initialized_units.push_back(u4);
    initialized_units.push_back(u5);

	for (long unsigned int i = 0; i < initialized_units.size(); ++i) {
		/* not sure how to use builder */
		if (initialized_units[i]) {
			std::cout << "pushing unit\n";
			sf::Vector2f location(50, (50 * i) + 100);
			initialized_units[i]->setLocation(location);
			units.push_back(std::shared_ptr<Unit> (initialized_units[i])); 
		}
		else
			std::cerr << "failed to build unit\n";
	}
	std::cout << "built deck\n";
}

void Deck::draw(sf::RenderWindow* window){

    for(int i = 0; i < MAX_UNITS; i++){
        //if (units[i]->getisActive()){
            units[i]->draw(window);
        //}
    }
}

std::vector<std::shared_ptr<Unit>>& Deck::getUnits(){
    return units;
}

Unit* Deck::generateKing(int alliance)
{
    return director.buildKing(alliance);
}

Unit* Deck::generateTowers(int alliance)
{
    return director.buildTower(alliance);
}
// void Deck::addUnit(Unit* unit){
//     if (current_no_units < 5){
//         units.push_back(unit);
//         current_no_units++;
//         std:: cout << "Unit added successfully\n";
//         return;
//     }

//     std:: cout << "List full, please replace a unit to continue\n";
// }

// void Deck::replaceUnit(Unit* unit, Unit* to_be_replaced){
//     for(int i = 0; i < current_no_units; i++){
//         if (units[i] == to_be_replaced){
//             units[i] = unit;
//             std:: cout << "Unit successfully found and replaced\n";
//             return;
//         }
//     }
//     std:: cout << "Unit to be replaced not found\n";
// }

Unit* Deck::getPickedUnit() {
	for (const auto& unit: units) {
		if (unit->getIsPicked())
			return unit.get();
	}
	return nullptr;
}

