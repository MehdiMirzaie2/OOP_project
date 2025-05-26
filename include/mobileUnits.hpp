#ifndef MOBILEUNITS_HPP_
#define MOBILEUNITS_HPP_

#include "Unit.hpp"

class mobileUnit : public Unit
{
    private:

    sf::Texture m_unitTextureIdle;
	sf::Texture m_unitTextureAttacking;
    sf::Vector2i m_dydx;
    sf::Vector2f m_deckPos;
    sf::Clock m_MoveClock;

    std::string m_unitTextureIdleName;
	std::string m_unitTextureAttackingName;

    bool m_isMovingForward;
	std::stack<Pair> m_path; 

    public:

}

// DIRECTOR RETURNS A POINTER TO A UNIT, STORE IT IN A MOBILE UNIT IF ITS A TROOP OR A SSTATIC UNIT IF ITS A TOWER OR A KING
// ACTIVE UNITS HAS BOTH STATIC UNITS AND MOBILE UNITS -> POLYMORPHISM
// FIX FILE I/O



#endif // MOBILEUNITS_HPP_