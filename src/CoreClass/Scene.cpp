#include "Scene.hpp"

size_t Scene::counter = 0;

// CONSTRUCTOR DESTRUCTOR //

Scene::Scene(void) : 	_id(counter)
{
	std::stringstream	ss;

	ss << "Scene" << _id;
	name = ss.str();
	counter++;
	std::cout << "construct "<< name << std::endl;
}

Scene::Scene(std::string n) : 	_id(counter)
{
	name = n;
	counter++;
	std::cout << "construct "<< name << std::endl;
}

Scene::~Scene(void)
{
	std::cout << "destruct " << name << std::endl; 
	std::list<GameObject*>::iterator go = _listGameObject.begin();
	for (; go != _listGameObject.end(); go++)
		delete *go;
}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Scene const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void					Scene::Save(std::ofstream &file)
{
	file << "\tSCENE : " << name << std::endl;
	std::list<GameObject *>::iterator it = _listGameObject.begin();
	for (;it != _listGameObject.end();it++)
		(*it)->Save(file);
}

void					Scene::InstanciatePrefab(GameObject *prefab) 
{ 
	GameObject* instance = new GameObject(*prefab);
	_listGameObject.push_back(instance);
}

std::string				Scene::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

GameObject*				Scene::FindGameObject(std::string name)
{
	std::list<GameObject*>::iterator go = _listGameObject.begin();
	for (; go != _listGameObject.end(); go++)
	{
		if ((*go)->name == name)
			return *go;
	}
	throw DError() << msg("FindGameObject(), resquested GameObject not found.");
}


// PRIVATE //

// GETTER SETTER //

std::list<GameObject*>	Scene::GetGameObjectList() const {return _listGameObject;}
