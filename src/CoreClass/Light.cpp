#include "Light.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Light::Light(float intens, glm::vec3 col)
{
	std::cout << "Construct Light" << std::endl;
	type = "Light";
	intensity = intens;
	color = col;
}

Light::Light(Light const & src)
{
	std::cout << "Construct Light" << std::endl;
	type = "Light";
	*this = src;
}

Light::~Light(void)
{
	std::cout << "Destruct Light" << std::endl;
}

// OVERLOADS //

Light	&Light::operator=(Light const & rhs)
{
	intensity = rhs.intensity;
	color = rhs.color;
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
	ss << "# Component Light #" << std::endl
	<< "intensity : " << intensity;
	return ss.str();
}

void			Light::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
	 	TABS = "\t\t\t";
	file << TABS << "LIGHT:" << intensity
	<< std::endl;
}

// PRIVATE //

// GETTER SETTER //
