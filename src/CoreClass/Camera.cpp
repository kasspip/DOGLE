#include "Camera.hpp"

// CONSTRUCTOR DESTRUCTOR //

Camera::Camera(void)
{

}

Camera::Camera(Camera const & src)
{
	*this = src;
}

Camera::~Camera(void)
{

}

// OVERLOADS //

Camera	&Camera::operator=(Camera const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Camera const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Camera::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Camera #";
	return ss.str();
}

void			Camera::Save(std::ofstream &file)
{
	file << "\t\t\tCAMERA : " << std::endl;
}

// PRIVATE //

// GETTER SETTER //
