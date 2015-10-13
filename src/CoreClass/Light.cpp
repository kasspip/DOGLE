#include "Light.hpp"

// CONSTRUCTOR DESTRUCTOR //

Light::Light(void)
{

}

Light::Light(Light const & src)
{
	*this = src;
}

Light::~Light(void)
{

}

// OVERLOADS //

Light	&Light::operator=(Light const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Light const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Light::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Light #";
	return ss.str();
}

void			Light::Save(std::ofstream &file)
{
	file << "\t\t\tLIGHT : " << std::endl;
}

// PRIVATE //

// GETTER SETTER //
