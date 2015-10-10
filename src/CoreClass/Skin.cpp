#include "Skin.hpp"

// CONSTRUCTOR DESTRUCTOR //

Skin::Skin(void)
{
	std::cout << "construct Skin" << std::endl;
}

Skin::Skin(Skin const & src)
{
	*this = src;
}

Skin::~Skin(void)
{
	std::cout << "destruct Skin" << std::endl;
}

// OVERLOADS //

Skin	&Skin::operator=(Skin const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Skin const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Skin::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void			Skin::Save(std::ofstream &file)
{
	file << "\t\t\tSKIN : " << std::endl;
}

// PRIVATE //

// GETTER SETTER //
