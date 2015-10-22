#include "Application.hpp"

// CONSTRUCTOR DESTRUCTOR //
Application	*Application::singleton = nullptr;

Application::Application(std::string name, int width, int height) : name(name), winW(width), winH(height)
{
	_currentScene = nullptr;
	_sceneToLoad = nullptr;
	_appShouldClose = false;
	shaderProgram3D = 0;
	shaderProgramDebug = 0;
	std::cout << "construct " + name << std::endl;
	singleton = this;
}

Application::~Application(void)
{
	std::cout << "destuct " + name << std::endl;
	for (Scene*	scene : _listScene)
		delete scene;
	for (GameObject* prefab : _listPrefab)
		delete prefab;
}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Application const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Application::LoadScene(Scene* scene)
{
	_sceneToLoad = scene;
}

void			Application::LoadScene(std::string name)
{
	_sceneToLoad = FindScene(name);
}

void			Application::AddPrefab(GameObject* gameObject) 
{ 
	_listPrefab.push_back(gameObject);
}

void			Application::Stop()
{
	_appShouldClose = true;
	glfwSetWindowShouldClose(window, GL_TRUE);
}

GameObject*		Application::FindPrefab(std::string name)
{
	for (GameObject* go : _listPrefab)
	{
		if (go->name == name)
			return go;
	}
	throw DError() << msg("FindPrefab(), resquested prefab not found.");
}

void			Application::Save(void)
{
	std::ofstream	file;
	
	std::cout << "Saving application in : " << name << ".dogle" << std::endl;
	file.open(name + ".dogle");

	file 	<< "# APPLICATION 			<name> <window W> <window H>" << std::endl
			<< "# SCENE 				<name>" << std::endl
			<< "# PREFAB | GAMEOBJECT 	<name>" << std::endl
			<< "# TRANSFORM 			<vec3 position> <vec3 rotation> <vec3 scale>" << std::endl
			<< "# SKIN 					<file name .dae>" << std::endl
			<< "# SCRIPT 				<class name>" << std::endl
			<< "# CAMERA 				<fov> <clip near> <clip far>" << std::endl
			<< std::endl;

	file << "APPLICATION:"
	<< name << SEPARATOR
	<< winW << SEPARATOR
	<< winH << std::endl;
	for (GameObject* prefab : _listPrefab)
		prefab->Save(file);
	for (Scene* scene : _listScene)
		scene->Save(file);
	file.close();
}

void			Application::AddScene(Scene* scene)
{ 
	_listScene.push_back(scene);
	if (_sceneToLoad == nullptr)
		_sceneToLoad = scene;
}

Scene*			Application::FindScene(std::string name)
{
	for (Scene* scene : _listScene)
	{
		if (scene->name == name)
			return scene;
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
Scene*			Application::GetSceneToLoad() { return _sceneToLoad ; }
void			Application::SetCurrentScene(Scene* scene) { _currentScene = scene; }
bool			Application::GetStop() { return _appShouldClose; }