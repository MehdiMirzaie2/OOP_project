#include "../../include/Elixir.hpp"
#include <iostream>

Elixir::Elixir() : m_amount(0), m_max(8) {}

void Elixir::update()
{
	// std::cout << "updating elixir\n";
	if (m_timer.getElapsedTime().asSeconds() >= 3.0f)
	{
		std::cout << "new amount = " << m_amount << std::endl;
		if (m_amount < m_max)
			m_amount++;
		m_timer.restart();
	}
}

int Elixir::getElixir() { return m_amount; }

void Elixir::decreaseElixir(int amount)
{
	m_amount -= amount;
}
