#include "Unit.hpp"

Unit::Unit()
{
	std::cout << "unit default constructor called\n";
}

Unit::Unit(t_unit _values)
{
	std::cout << "unit constructor called\n";
	this->values = _values;
}

Unit &Unit::operator=(const Unit &_src)
{
	std::cout << "unit copy assignment constructor called\n";
}

Unit::Unit(const Unit &_src)
{
	std::cout << "unit copy constructor called\n";
}

Unit::~Unit()
{
	std::cout << "unit destructor called\n";
}