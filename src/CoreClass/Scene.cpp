#include "Scene.hpp"

// CONSTRUCTOR DESTRUCTOR //

Scene::Scene(void)
{
	std::cout << "construct Scene" << std::endl;

}

Scene::Scene(Scene const & src)
{
	*this = src;
}

Scene::~Scene(void)
{
	std::cout << "destruct Scene" << std::endl; 

}

// OVERLOADS //

Scene	&Scene::operator=(Scene const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Scene const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Scene::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void	Scene::AddGameObject(GameObject *gameObject) 
{ 
	_listGameObject.push_back(gameObject);
}

// PRIVATE //

// GETTER SETTER //
