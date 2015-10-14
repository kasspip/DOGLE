#include "Application.hpp"

// CONSTRUCTOR DESTRUCTOR //

Application::Application(void) : name("AppName")
{
	_currentScene = NULL;
	appShouldClose = false;
	winW = 1280;
	winH = 1280;
	shaderProgram3D = 0;
	shaderProgramDebug = 0;
	std::cout << "construct " + name << std::endl;
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
		PRINT_DEBUG( "> Loading \'" + (*go)->name + "\'");
		if ((skin = (*go)->GetComponent<Skin>()))
		{
			if (skin->GetIsBind() == false)
			{
				PRINT_DEBUG( "\tBinding skin");
				_SkinVBO(*skin);
				_SkinVAO(*skin);
				skin->SetIsBind(true);
				skin = NULL;
			}
		}
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

void			Application::_BindBuffer(GLfloat *data, GLuint dataSize, GLuint *id)
{
	glGenBuffers(1, id);
	glBindBuffer(GL_ARRAY_BUFFER, *id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dataSize, data, GL_STATIC_DRAW);
}

void			Application::_SkinVBO(Skin& skin)
{
	PRINT_DEBUG("\tBind VBO");
	_BindBuffer(skin.positions, skin.nb_vertices * 3, &(skin.positionsBind));
	_BindBuffer(skin.UVs, skin.nb_vertices * 2, &(skin.UVsBind));
	_BindBuffer(skin.normals, skin.nb_vertices * 3, &(skin.normalsBind));
}

void			Application::_BindAttribut(GLuint bufferId, GLuint attributId, int pSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glVertexAttribPointer(attributId, pSize, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(attributId);
}

void			Application::_SkinVAO(Skin& skin)
{
	PRINT_DEBUG("\tBind VAO");

	glGenVertexArrays(1, &(skin.vao));
	glBindVertexArray(skin.vao);
	GLuint	attributId = 0;
	_BindAttribut(skin.positionsBind, attributId++, 3);
	_BindAttribut(skin.UVsBind, attributId++, 2);
	_BindAttribut(skin.normalsBind, attributId++, 3);
}

// GETTER SETTER //

Scene*			Application::GetCurrentScene() { return _currentScene; }
