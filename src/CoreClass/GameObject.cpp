#include "GameObject.hpp"
#include "Transform.hpp"

// CONSTRUCTOR DESTRUCTOR //

GameObject::GameObject(void)
{
	std::cout << "construct GameObject" << std::endl;
	AddComponent(new Transform);
}

GameObject::GameObject(GameObject const & src)
{
	*this = src;
}

GameObject::~GameObject(void)
{
	std::cout << "destruct GameObject" << std::endl;
	std::list<IComponent*>::iterator it = _listComponent.begin();
	for (; it != _listComponent.end(); it++)
		delete *it;
}

// OVERLOADS //

GameObject	&GameObject::operator=(GameObject const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, GameObject const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		GameObject::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void	GameObject::AddComponent(IComponent *compt)
{
	_listComponent.push_back(compt);
}

// PRIVATE //

// GETTER SETTER //
