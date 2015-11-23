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
	for (GameObject* go : _listGameObject)
		delete go;
	for (GameObject* go : _listBindGameObject)
		delete go;
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
	file << "\tSCENE:"
	<< name << std::endl;
	for (GameObject* go : _listBindGameObject)
		go->Save(file);
	for (GameObject* go : _listGameObject)
		go->Save(file);
}

GameObject				*Scene::AddGameObject(GameObject* go)
{
	_listBindGameObject.push_back(go);
	return (go);
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

void					Scene::DeleteInstance(std::string n) 
{ 
	std::list<GameObject*>::iterator it = _listBindGameObject.begin();
	for (; it != _listBindGameObject.end(); it++)
	{
		if ((*it)->name == n)
		{
			delete *it;
			_listBindGameObject.erase(it);
			break ;
		}
	}

	it = _listGameObject.begin();
	for (; it != _listGameObject.end(); it++)
	{
		if ((*it)->name == n)
		{
			delete *it;
			_listBindGameObject.erase(it);
			break ;
		}
	}
}

std::string				Scene::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

GameObject*				Scene::FindGameObject(std::string n)
{
	for (GameObject* go : _listGameObject)
	{
		if (go->name == n)
			return go;
	}
		for (GameObject* go : _listBindGameObject)
	{
		if (go->name == n)
			return go;
	}
	throw DError() << msg("FindGameObject(): No GameObject " + n + " found in scene " + name);
}

// PRIVATE //

// GETTER SETTER //

std::list<GameObject*>	&Scene::GetGameObjectList() {return _listGameObject;}
std::list<GameObject*>	&Scene::GetBindGameObjectList() {return _listBindGameObject;}

