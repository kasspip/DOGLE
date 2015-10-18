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
	Skin				*skin = NULL;
	Script				*script = NULL;
	std::list<GameObject*>	&lst_bind = app.GetCurrentScene()->GetBindGameObjectList();
	std::list<GameObject*>	&lst_cur = app.GetCurrentScene()->GetGameObjectList();

	for (GameObject *go : lst_bind)
	{
		std::cout << ("> Loading \'" + go->name + "\'\n");

		if ((skin = go->GetComponent<Skin>()))
		{
			if (skin->GetIsBind() == false)
			{
				PRINT_DEBUG( "\tBinding buffers");
				skin->SkinVBO();
				skin->SkinVAO();
				PRINT_DEBUG( "\tBinding texture");
				skin->SkinTexture();
				skin->SetIsBind(true);
				skin = NULL;
			}
		}
		if ((script = go->GetComponent<Script>()))
		{
			script->Awake();
			script = NULL;
		}
	}
	lst_cur.insert(lst_cur.end(), lst_bind.begin(), lst_bind.end());
	lst_bind.clear();
	
	currentState = STATE_PHYSICS;

}

std::string		Start::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //



// GETTER SETTER //
