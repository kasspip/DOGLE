#include "Application.hpp"

// CONSTRUCTOR DESTRUCTOR //

Application::Application(void)
{
	std::cout << "construct application" << std::endl;
}

Application::Application(Application const & src)
{
	*this = src;
}

Application::~Application(void)
{
	std::cout << "destruct application" << std::endl;
}

// OVERLOADS //

Application	&Application::operator=(Application const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Application const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Application::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void		Application::AddScene(Scene *scene)
{ 
	_listScene.push_back(scene);
}

// PRIVATE //

// GETTER SETTER //
