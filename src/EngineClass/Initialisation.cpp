#include "Initialisation.hpp"

// CONSTRUCTOR DESTRUCTOR //

Initialisation::Initialisation(void)
{
	std::cout << " CONSTRUCT Initialisation " << std::endl;
}

Initialisation::Initialisation(Initialisation const & src)
{
	*this = src;
}

Initialisation::~Initialisation(void)
{

}

// OVERLOADS //

Initialisation	&Initialisation::operator=(Initialisation const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Initialisation const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Initialisation::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
