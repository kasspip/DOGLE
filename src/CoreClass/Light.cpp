#include "Light.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Light::Light(void)
{
	name = "Light";
}

Light::Light(Light const & src)
{
	name = "Skin";
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
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
	 	TABS = "\t\t\t";
	file << TABS << "LIGHT" << std::endl;
}

// PRIVATE //

// GETTER SETTER //
