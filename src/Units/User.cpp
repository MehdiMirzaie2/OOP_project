#include "../../include/User.hpp"

User::User(std:: string name){
    this->name = name;
    wins = 0;
    losses = 0;
    current_no_units = 0;
    units = new Unit*[5];
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

void User::fight_user(User other){
    // to be done
};

Unit** User::getUnits(){
    return units;
}

void User::addUnit(Unit* unit){
    if (current_no_units < 5){
        units[current_no_units] = unit;
        current_no_units++;
        std:: cout << "Unit added successfully\n";
    }
    std:: cout << "List full, please replace a unit to continue\n";
}

void User::replaceUnit(Unit* unit, Unit* to_be_replaced){
    for(int i = 0; i < current_no_units; i++){
        if (units[i] == to_be_replaced){
            units[i] = unit;
            std:: cout << "Unit successfully found and replaced\n";
            return;
        }
    }
    std:: cout << "Unit to be replaced not found\n";
}

Unit** User::getTowers(){return towers;}
Unit** User::getKing(){return king;}