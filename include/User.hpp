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
    int m_wins; // Number of wins
    int m_losses; // Number of losses
    std::string m_name; // Player's name
    std::unique_ptr<Elixir> m_elixir; // Player's elixir resource manager
    std::array<std::shared_ptr<Unit>, 2> m_towers; // Player's two tower units
    
    std::unique_ptr<Deck> m_unitDeck; // Player's unit deck

public:
    // Constructors
    User(); // Default constructor
    User(std::string name, int left_or_right); // Constructor with name and side choice

    // Getters
    int getWins(); // Returns number of wins
    int getLosses(); // Returns number of losses
    std::string getName(); // Returns player name
    Deck *getDeck(); // Returns pointer to player's deck
    std::array<std::shared_ptr<Unit>,2> getTowers();
    Elixir *getElixir(); // Returns pointer to player's elixir

    // Setters
    void setWins(int w); // Sets wins count
    void setLosses(int l); // Sets losses count
    void setName(std::string new_name); // Sets player name

    // Utility methods
    void update(sf::Vector2i); // Updates player state with input vector
    void draw(sf::RenderWindow *window); // Draws player-related visuals on window
};

#endif // UNITS_HEADER_USER_HPP_
