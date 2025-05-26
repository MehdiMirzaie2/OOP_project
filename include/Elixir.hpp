#ifndef ELIXIR_HPP
#define ELIXIR_HPP

#include <SFML/Graphics.hpp>

class Elixir {
	private:
		int m_amount;
		int m_max;
		int elixir; 
		sf::Clock m_timer;

	public:
		Elixir();

		void update();
		int getElixir();
		void decreaseElixir(int amount);
		void setElixir(int amount);
};


#endif
