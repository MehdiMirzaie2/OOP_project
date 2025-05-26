#ifndef ELIXIR_HPP
#define ELIXIR_HPP

#include <SFML/Graphics.hpp>

class Elixir
{
private:
	int m_amount;
	int m_max;
	sf::Clock m_timer;

public:
	Elixir();

	void update();
	int getElixir();
	void decreaseElixir(int amount);
};

#endif
