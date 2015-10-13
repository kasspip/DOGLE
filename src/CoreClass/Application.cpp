#include "Application.hpp"

// CONSTRUCTOR DESTRUCTOR //

Application::Application(void) : name("AppName")
{
	_currentScene = NULL;
	std::cout << "construct " + name << std::endl;
}

Application::Application(std::string name) : name(name)
{
	_currentScene = NULL;
	std::cout << "construct " + name << std::endl;
}

Application::Application(Application const & src)
{
	*this = src;
}

Application::~Application(void)
{
	std::cout << "destuct " + name << std::endl;
	std::list<GameObject*>::iterator prefab = _listPrefab.begin();
	for (; prefab != _listPrefab.end(); prefab++)
		delete *prefab;

	std::list<Scene*>::iterator scene = _listScene.begin();
	for (; scene != _listScene.end(); scene++)
		delete *scene;
}

// OVERLOADS //

Application	&Application::operator=(Application const & rhs)
{
	(void)rhs;
	throw DError() << msg ("Application operator= not yet implemented");
	return *this;
}

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

void			Application::LoadScene(Scene* scene)
{
	if (scene == NULL)
		throw DError() << msg("Application.LoadScene(), NULL pointer");

	// TODO 
	// Nettoyer la scene precedente

	_currentScene = scene;
	std::list<GameObject*> GameObjects = scene->GetGameObjectList();
	std::list<GameObject*>::iterator go = GameObjects.begin();

	Skin* skin = NULL;

	for (; go != GameObjects.end(); go++)
	{
		std::cout << "> Loading \'" << (*go)->name << "\'" << std::endl;
		if ((skin = (*go)->GetComponent<Skin>()))
			_SkinBindBuffers(*skin);
	}
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

void			Application::_SkinBindBuffers(Skin& skin)
{
	(void)skin;
	std::cout << "bind buffer" << std::endl;
}


// GETTER SETTER //

Scene*			Application::GetCurrentScene() { return _currentScene; }
