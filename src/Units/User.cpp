#include "../../include/User.hpp"

User::User(){};

User::User(std:: string name){
    this->name = name;
    wins = 0;
    losses = 0;
    towers = nullptr;
    king = nullptr;
    m_elixir = std::make_unique<Elixir>();
    unitDeck = std::make_unique<Deck>();
}

User::User(std:: string name, int left_or_right){
    this->name = name;
    wins = 0;
    losses = 0;
    towers = nullptr;
    king = nullptr;
    m_elixir = std::make_unique<Elixir>();
    unitDeck = std::make_unique<Deck>(left_or_right);
}

Elixir* User::getElixir() {
	return m_elixir.get();
}

void User::update(sf::Vector2i mouse_pos) {
	m_elixir->update();

	for (const auto& unit: unitDeck->getUnits()) {
		unit->moveIfPicked(mouse_pos);
	}
}

void User::setLosses(int l){
    losses = l;
}

void User::setWins(int w){
    wins = w;
}

void User::setName(std::string new_name){
    name = new_name;
}
/*
void User::setElixir(int new_elixir){
    elixir = new_elixir;
}
*/
int User::getWins(){return wins;}
int User::getLosses(){return losses;}
std:: string User::getName(){return name;}

/*
int User::getElixir(){
    return elixir;
}
*/

// void User::fight_user(User other){
//     // to be done
// };

Unit* User::getTowers(){return towers;}
Unit* User::getKing(){return king;}

void User::draw(sf::RenderWindow* window){
    unitDeck->draw(window);
}

Deck* User::getDeck(){
    return unitDeck.get();
}

void User::deploy(int index, sf::Vector2f dep_loc)
{   
    int col = dep_loc.x / 30, row = dep_loc.y / 30;
    std::cout << row << " " << col << std::endl;
	Unit* unit = unitDeck->getUnits()[index].get();
    //sf::Vector2i screen_pos = sf::Vector2i(30 * dep_loc.x, 30 * dep_loc * 30);
    //dep_loc.x *= 30;
    //dep_loc.y *= 30;
	sf::Vector2f a = sf::Vector2f(col * 30, row * 30);
    unit->setLocation(a);
    std:: cout << "UNITS LOCATION: " << unit->getLocation().x << std::endl;
    unit->setisActive(true);
}


