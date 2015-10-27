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

std::string				Scene::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

GameObject*				Scene::FindGameObject(std::string name)
{
	for (GameObject* go : _listGameObject)
	{
		if (go->name == name)
			return go;
	}
		for (GameObject* go : _listBindGameObject)
	{
		if (go->name == name)
			return go;
	}
	throw DError() << msg("FindGameObject(), resquested GameObject not found.");
}

// PRIVATE //

// GETTER SETTER //

std::list<GameObject*>	&Scene::GetGameObjectList() {return _listGameObject;}
std::list<GameObject*>	&Scene::GetBindGameObjectList() {return _listBindGameObject;}

