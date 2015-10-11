#include "Scene.hpp"

size_t Scene::counter = 0;

// CONSTRUCTOR DESTRUCTOR //

Scene::Scene(void) : 	_id(counter)
{
	std::stringstream	ss;

	ss << "Scene" << _id;
	_name = ss.str();
	counter++;
	std::cout << "construct "<< _name << std::endl;
}

Scene::Scene(std::string name) : 	_id(counter),
									_name(name)
{
	counter++;
	std::cout << "construct "<< _name << std::endl;
}

Scene::Scene(Scene const & src)
{
	*this = src;
}

Scene::~Scene(void)
{
	std::cout << "destruct " << _name << std::endl; 
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



void			Scene::Save(std::ofstream &file)
{
	file << "\tSCENE : " << _name << std::endl;
	std::list<GameObject *>::iterator it = _listGameObject.begin();
	for (;it != _listGameObject.end();it++)
		(*it)->Save(file);
}

void			Scene::AddGameObject(GameObject *gameObject) 
{ 
	_listGameObject.push_back(gameObject);
}

std::string		Scene::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}
// PRIVATE //

// GETTER SETTER //

std::list<GameObject *>		Scene::GetGameObjectList() {return _listGameObject;}