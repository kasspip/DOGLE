#include "Start.hpp"
#include "Script.hpp"
#include "Physics.hpp"

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
	if (app.GetSceneToLoad() != nullptr)
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

	for (GameObject* go : scene->GetGameObjectList())
		delete go;
	scene->GetGameObjectList().clear();
	for (GameObject* go : scene->GetBindGameObjectList())
		delete go;
	scene->GetBindGameObjectList().clear();
}

GameObject*			Start::_FindFirstCamera(Scene* scene)
{
	Camera* cam = nullptr;
	for(GameObject* go : scene->GetGameObjectList())
	{
		if ((cam = go->GetComponent<Camera>()))
		{
			std::cout << "-> Set Main camera on " << go->name << std::endl;
			return go;
		}
	}
	for(GameObject* go : scene->GetBindGameObjectList())
	{
		if ((cam = go->GetComponent<Camera>()))
		{
			std::cout << "-> Set Main camera on " << go->name << std::endl;
			return go;
		}
	}
	return nullptr;
}

void			Start::_SwapScene(Application & app)
{
	if (app.GetCurrentScene() != nullptr)	
		_CleanOldScene(app.GetCurrentScene());
	
	app.SetCurrentScene(app.GetSceneToLoad());
	std::cout << "LoadScene(): " << app.GetCurrentScene()->name << std::endl;
	GameObject* cam = _FindFirstCamera(app.GetCurrentScene());
	if (cam == nullptr)
		throw DError() << msg("Can't find a Camera in scene " + app.GetCurrentScene()->name);
	Camera::SetMainCamera(cam);
	app.LoadScene(nullptr);
}

void			Start::_AwakeNewGameObects(Application & app)
{
	std::list<GameObject*>	&lst_bind = app.GetCurrentScene()->GetBindGameObjectList();
	std::list<GameObject*>	&lst_cur = app.GetCurrentScene()->GetGameObjectList();
	Script			*script = nullptr;
	for (GameObject *go : lst_bind)
	{
		for (IComponent* compo : go->_listComponent)
		{
			if ((script = dynamic_cast<Script*>(compo)))
			{
				script->Awake();
				script = nullptr;
			}
		}
	}
	Skin					*skin = nullptr;
	Collider				*collider = nullptr;
	Text					*text = nullptr;
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
				skin = nullptr;
			}
		}
		if ((collider = go->GetComponent<Collider>()))
		{
			if (collider->isPhy == false)
			{
				PRINT_DEBUG("ADD world phy");
				Physics::singleton->InstantiateGo(collider->physic_ptr);
				collider->isPhy= true;
				collider = nullptr;
			}
		}
		if ((text = go->GetComponent<Text>()))
		{
			if (text->isInit == false)
			{
				PRINT_DEBUG("Init text: " + text->text);
				std::cout << "Init text: " << text->text << std::endl;;
				text->LoadFont(app.winW, app.winH);
				text->isInit = true;
				text = nullptr;
			}
		}
	}
	lst_cur.insert(lst_cur.end(), lst_bind.begin(), lst_bind.end());
	lst_bind.clear();
}

// GETTER SETTER //
