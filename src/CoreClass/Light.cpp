#include "Light.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Light::Light(glm::vec3 col)
{
	std::cout << "Construct Light" << std::endl;
	type = "Light";
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
	<< "Color : " << color.x << "," << color.y << "," << color.z ;
	return ss.str();
}

void			Light::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
	 	TABS = "\t\t\t";
	file 	<< TABS << "LIGHT:" 
			<< color.x << SEPARATOR_F << color.y << SEPARATOR_F << color.z 
			<< std::endl;
}

// PRIVATE //

// GETTER SETTER //
