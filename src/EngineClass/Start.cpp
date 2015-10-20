#include "Start.hpp"
#include "Script.hpp"

// CONSTRUCTOR DESTRUCTOR //

Start::Start(void)
{
}

Start::~Start(void)
{
}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Start const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Start::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Start>");
	
	if (app.GetSceneToLoad() != NULL)
		_SwapScene(app);
	if (app.GetCurrentScene()->GetBindGameObjectList().size() > 0)
		_AwakeNewGameObects(app);

	currentState = STATE_PHYSICS;
}

std::string		Start::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

void			Start::_CleanOldScene(Scene* scene)
{
	(void)scene;
	// TODO //
}

GameObject*			Start::_FindFirstCamera(Scene* scene)
{
	Camera* cam = NULL;
	for(GameObject* go : scene->GetBindGameObjectList())
	{
		if ((cam = go->GetComponent<Camera>()))
		{
			std::cout << "Set Main camera on " << go->name << std::endl;
			return go;
		}
	}
	for(GameObject* go : scene->GetGameObjectList())
	{
		if ((cam = go->GetComponent<Camera>()))
		{
			std::cout << "Set Main camera on " << go->name << std::endl;
			return go;
		}
	}
	return NULL;
}

void			Start::_SwapScene(Application & app)
{
	if (app.GetCurrentScene() != NULL)	
		_CleanOldScene(app.GetCurrentScene());
	
	app.SetCurrentScene(app.GetSceneToLoad());

	GameObject* cam = _FindFirstCamera(app.GetCurrentScene());
	if (cam == NULL)
		throw DError() << msg("Can't find a Camera in scene " + app.GetCurrentScene()->name);
	Camera::SetMainCamera(cam);
	app.LoadScene(NULL);
}

void			Start::_AwakeNewGameObects(Application & app)
{
	Skin				*skin = NULL;
	Script				*script = NULL;
	std::list<GameObject*>	&lst_bind = app.GetCurrentScene()->GetBindGameObjectList();
	std::list<GameObject*>	&lst_cur = app.GetCurrentScene()->GetGameObjectList();

	for (GameObject *go : lst_bind)
	{
		PRINT_DEBUG("> Awaking GameObject: \'" + go->name + "\'\n");
		if ((skin = go->GetComponent<Skin>()))
		{
			if (skin->GetIsBind() == false)
			{
				PRINT_DEBUG("Binding skin");
				skin->SkinVBO();
				skin->SkinVAO();
				skin->SkinTexture();
				skin->SetIsBind(true);
				skin = NULL;
			}
		}
		if ((script = go->GetComponent<Script>()))
		{
			PRINT_DEBUG("Calling Awake() from " + script->name);
			script->Awake();
			script = NULL;
		}
	}
	lst_cur.insert(lst_cur.end(), lst_bind.begin(), lst_bind.end());
	lst_bind.clear();
}

// GETTER SETTER //
