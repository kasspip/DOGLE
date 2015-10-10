#include "GameObject.hpp"
#include "Transform.hpp"

size_t GameObject::counter = 0;

// CONSTRUCTOR DESTRUCTOR //

GameObject::GameObject(void) :	_id(counter)
{
	std::stringstream	ss;

	ss << "GameObject " << _id;
	_name = ss.str();
	counter++;
	std::cout << "construct GameObject" << std::endl;
	AddComponent(new Transform);
}

GameObject::GameObject(std::string name) :	_id(counter),
											_name(name)
{
	counter++;
	std::cout << "construct "<< _name << std::endl;
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

void			GameObject::Save(std::ofstream &file)
{
	file << "\t\tGAMEOBJECT : " << _name << std::endl;
	std::list<IComponent *>::iterator it = _listComponent.begin();
	for (;it != _listComponent.end();it++)
		(*it)->Save(file);
}

void	GameObject::AddComponent(IComponent *compt)
{
	_listComponent.push_back(compt);
}

// PRIVATE //

// GETTER SETTER //
