#include "Scene.hpp"

size_t Scene::counter = 0;

// CONSTRUCTOR DESTRUCTOR //

Scene::Scene(void) : 	_id(counter)
{
	std::stringstream	ss;

	ss << "Scene" << _id;
	name = ss.str();
	counter++;
	_currentCamera = nullptr;
	std::cout << "construct Scene "<< name << std::endl;
}

Scene::Scene(std::string n) : 	_id(counter)
{
	name = n;
	counter++;
	_currentCamera = nullptr;
	std::cout << "construct Scene "<< name << std::endl;
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

GameObject				*Scene::InstanciatePrefab(GameObject *prefab) 
{
	GameObject* instance = new GameObject(*prefab);
	_listBindGameObject.push_back(instance);
	return (instance);
}

GameObject				*Scene::InstanciatePrefab(GameObject *prefab, Transform tr) 
{
	GameObject* instance = new GameObject(*prefab);
	*(instance->GetComponent<Transform>()) = tr;
	_listBindGameObject.push_back(instance);
	return (instance);
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

std::list<GameObject*>	&Scene::GetGameObjectList() {return _listGameObject;}
std::list<GameObject*>	&Scene::GetBindGameObjectList() {return _listBindGameObject;}

