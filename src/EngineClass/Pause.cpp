#include "Pause.hpp"
#include "Script.hpp"
#include "Engine.hpp"

// CONSTRUCTOR DESTRUCTOR //

Pause::Pause(void)
{

}

Pause::~Pause(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Pause const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Pause::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Pause>");

	Script* script = nullptr;
	for (GameObject* go : app.GetCurrentScene()->GetGameObjectList())
	{
		if ((script = go->GetComponent<Script>()))
		{
			script->OnPause();
			script = nullptr;
		}
	}
	(Engine::singleton->pause == false) ? currentState = STATE_DESTROY : currentState = STATE_INPUTS ;
}

std::string		Pause::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
