#include "Application.hpp"

// CONSTRUCTOR DESTRUCTOR //
Application	*Application::singleton = NULL;


Application::Application(void) : name("AppName")
{
	_currentScene = NULL;
	appShouldClose = false;
	winW = 1280;
	winH = 1280;
	shaderProgram3D = 0;
	shaderProgramDebug = 0;
	std::cout << "construct " + name << std::endl;
	singleton = this;
}

Application::Application(std::string name) : name(name)
{
	_currentScene = NULL;
	appShouldClose = false;
	winW = 1280;
	winH = 1280;
	shaderProgram3D = 0;
	shaderProgramDebug = 0;
	std::cout << "construct " + name << std::endl;
	singleton = this;
}

Application::~Application(void)
{
	std::cout << "destuct " + name << std::endl;


	std::list<Scene*>::iterator scene = _listScene.begin();
	for (; scene != _listScene.end(); scene++)
		delete *scene;

	std::list<GameObject*>::iterator prefab = _listPrefab.begin();
	for (; prefab != _listPrefab.end(); prefab++)
		delete *prefab;
}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Application const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Application::AddPrefab(GameObject* gameObject) 
{ 
	_listPrefab.push_back(gameObject);
}

GameObject*		Application::FindPrefab(std::string name)
{
	std::list<GameObject*>::iterator it = _listPrefab.begin();
	for (; it != _listPrefab.end(); it ++)
	{
		if ((*it)->name == name)
			return *it;
	}
	throw DError() << msg("FindPrefab(), resquested prefab not found.");
}

void			Application::Save(void)
{
	std::ofstream	file;

	file.open(name + ".dogle");
	file << "APPLICATION : " << name << std::endl;
	std::list<Scene *>::iterator it = _listScene.begin();
	for (;it != _listScene.end();it++)
		(*it)->Save(file);
	file.close();
}

void			Application::AddScene(Scene* scene)
{ 
	_listScene.push_back(scene);
	if (_currentScene == NULL)
		_currentScene = scene;
}

Scene*			Application::FindScene(std::string name)
{
	std::list<Scene*>::iterator it = _listScene.begin();
	for (; it != _listScene.end(); it++)
	{
		if ((*it)->name == name)
			return *it;
	}
	throw DError() << msg("FindScene(), resquested scene not found.");
}

std::string		Application::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //

Scene*			Application::GetCurrentScene() { return _currentScene; }
