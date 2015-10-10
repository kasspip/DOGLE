#include "Application.hpp"

// CONSTRUCTOR DESTRUCTOR //

Application::Application(void) : _name("AppName")
{
	std::cout << "construct " << _name << std::endl;
}

Application::Application(std::string name) : _name(name)
{
	std::cout << "construct " << _name << std::endl;
}

Application::Application(Application const & src)
{
	*this = src;
}

Application::~Application(void)
{
	std::cout << "destruct " << _name << std::endl;
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

void			Application::Save(void)
{
	std::ofstream	file;

	file.open(_name + ".dogle");
	file << "APPLICATION : " << _name << std::endl;
	std::list<Scene *>::iterator it = _listScene.begin();
	for (;it != _listScene.end();it++)
		(*it)->Save(file);
	file.close();
}

void		Application::AddScene(Scene *scene)
{ 
	_listScene.push_back(scene);
}

// PRIVATE //

// GETTER SETTER //
