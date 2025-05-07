#ifndef UNITS_HEADER_USER_HPP_
#define UNITS_HEADER_USER_HPP_

#include <string>
#include "Unit.hpp"

class User{
    private:
        int wins;
        int losses;
        std:: string name;
        int elixir;
        Unit** units; // pointer to pointers to units to allow polymorphism
        int current_no_units;
        Unit** towers;
        Unit** king;

    public:
        //initializers
        User(std:: string name);    

        //getters
        int getWins();
        int getLosses();
        std:: string getName();
        int getElixir();
        Unit** getUnits();
        Unit** getTowers();
        Unit** getKing();

        //setters
        void setWins(int w);
        void setLosses(int l);
        void setName(std:: string new_name);
        void setElixir(int new_elixir);
        void addUnit(Unit* unit);
        void replaceUnit(Unit* unit_new, Unit* to_be_replaced);

        void fight_user(User other);
         virtual void deploy(sf::Vector2f d_loc) = 0; //abstract class

};

#endif // UNITS_HEADER_USER_HPP_