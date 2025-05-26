#ifndef UNITS_HEADER_USER_HPP_
#define UNITS_HEADER_USER_HPP_

#include <string>
#include "Unit.hpp"
#include "Deck.hpp"
#include "Elixir.hpp"
#include <array>

class User
{
private:
        int wins;
        int losses;
        std::string name;
        std::unique_ptr<Elixir> m_elixir;
        std::array<std::shared_ptr<Unit>, 2> towers;
        std::shared_ptr<Unit> king;
        std::unique_ptr<Deck> unitDeck;

public:
        // initializers
        User();
        User(std::string name);
        User(std::string name, int left_or_right);
        
        // getters
        int getWins();
        int getLosses();
        std::string getName();
        Deck *getDeck();
        Elixir *getElixir();
        
        // setters
        void setWins(int w);
        void setLosses(int l);
        void setName(std::string new_name);
        void setElixir(int new_elixir);

        //utils
        void update(sf::Vector2i);
        void draw(sf::RenderWindow *window);
};

#endif // UNITS_HEADER_USER_HPP_
