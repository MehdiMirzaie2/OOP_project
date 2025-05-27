#ifndef ELIXIR_HPP
#define ELIXIR_HPP

#include <SFML/Graphics.hpp>

class Elixir
{
private:
	int m_amount; // Current amount of elixir
	int m_max; // Maximum elixir capacity
	sf::Clock m_timer; // Timer for elixir regeneration

public:
	Elixir(); // Constructor to initialize elixir state

	void update(); // Regenerates elixir over time
	int getElixir(); // Returns the current elixir amount
	void decreaseElixir(int amount); // Reduces elixir by a specified amount
};

#endif
