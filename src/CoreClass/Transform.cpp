#include "Transform.hpp"

// CONSTRUCTOR DESTRUCTOR //

Transform::Transform(void)
{
	std::cout << "construct Transform" << std::endl;
}

Transform::Transform(Transform const & src)
{
	*this = src;
}

Transform::~Transform(void)
{
	std::cout << "destruct Transform" << std::endl;
}

// OVERLOADS //

Transform	&Transform::operator=(Transform const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Transform const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Transform::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
