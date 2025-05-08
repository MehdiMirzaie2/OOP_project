#include "../../include/User.hpp"

User::User(){};

User::User(std:: string name){
    this->name = name;
    wins = 0;
    losses = 0;
    towers = nullptr;
    king = nullptr;
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

void User::setElixir(int new_elixir){
    elixir = new_elixir;
}

int User::getWins(){return wins;}
int User::getLosses(){return losses;}
std:: string User::getName(){return name;}

int User::getElixir(){
    return elixir;
}

// void User::fight_user(User other){
//     // to be done
// };

Unit** User::getTowers(){return towers;}
Unit** User::getKing(){return king;}

void User::draw(sf::RenderWindow* window){
    unitDeck.draw(window);
}

void User::deploy(Unit* unit, sf::Vector2f dep_loc)
{
    unit->setLocation(dep_loc);
    unit->setisActive(true);
    unit->draw();
}