#include "User.hpp"
#include <iostream> 

User::User() : wins(0), losses(0), name(""), m_elixir(new Elixir()), towers(nullptr), king(nullptr), unitDeck(new Deck()), elixirBar(8, 40, 30) {}

User::User(std::string name) : wins(0), losses(0), name(name), m_elixir(new Elixir()), towers(nullptr), king(nullptr), unitDeck(new Deck()), elixirBar(8, 40, 30) {}

User::User(std::string name, int left_or_right) : wins(0), losses(0), name(name), m_elixir(new Elixir()), towers(nullptr), king(nullptr), unitDeck(new Deck(left_or_right)), elixirBar(8, 40, 30) {}

User::~User() {
    delete m_elixir;
    delete unitDeck;
   
}

Elixir* User::getElixir() {
	return m_elixir;
}

void User::update(sf::Vector2i mouse_pos) {
    m_elixir->update();
    elixirBar.update(m_elixir->getElixir());

    for (auto unit : unitDeck->getUnits()) {
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

Unit** User::getTowers(){return towers;}
Unit** User::getKing(){return king;}

void User::draw(sf::RenderWindow& window) { // Change signature to reference
    unitDeck->draw(window);
    elixirBar.draw(window, 10.f, 10.f); // Pass x and y as required by ElixirBar
}

Deck* User::getDeck(){
    return unitDeck;
}

void User::deploy(int index, sf::Vector2i dep_loc)
{   
    int col = dep_loc.x / 30, row = dep_loc.y / 30;
    std::cout << row << " " << col << std::endl;
    Unit* unit = unitDeck->getUnits()[index];
    sf::Vector2i a = sf::Vector2i(col * 30, row * 30);
    unit->setLocation(a);
    std::cout << "UNITS LOCATION: " << unit->getLocation().x << std::endl;
    unit->setisActive(true);
}


