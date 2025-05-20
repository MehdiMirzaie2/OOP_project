#include "../../include/User.hpp"

User::User(){};

User::User(std:: string name){
    this->name = name;
    wins = 0;
    losses = 0;
    towers = nullptr;
    king = nullptr;
    m_elixir = new Elixir();
    unitDeck = new Deck();
}

Elixir* User::getElixir() {
	return m_elixir;
}

void User::update() {
	m_elixir->update();
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

Unit** User::getTowers(){return towers;}
Unit** User::getKing(){return king;}

void User::draw(sf::RenderWindow* window){
    unitDeck->draw(window);
}

Deck* User::getDeck(){
    return unitDeck;
}

void User::deploy(int index, sf::Vector2i dep_loc)
{   
    int col = dep_loc.x / 30, row = dep_loc.y / 30;
    std::cout << row << " " << col << std::endl;
	Unit* unit = unitDeck->getUnits()[index];
    //sf::Vector2i screen_pos = sf::Vector2i(30 * dep_loc.x, 30 * dep_loc * 30);
    //dep_loc.x *= 30;
    //dep_loc.y *= 30;
	sf::Vector2i a = sf::Vector2i(col * 30, row * 30);
    unit->setLocation(a);
    std:: cout << "UNITS LOCATION: " << unit->getLocation().x << std::endl;
    unit->setisActive(true);
}
