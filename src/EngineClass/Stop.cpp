#include "Stop.hpp"
#include "Script.hpp"

// CONSTRUCTOR DESTRUCTOR //

Stop::Stop(void)
{
}

Stop::~Stop(void)
{
}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Stop const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Stop::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Stop>");
	Script* script = nullptr;
	for (GameObject* go : app.GetCurrentScene()->GetGameObjectList())
	{
		for (IComponent* compo : go->_listComponent)
		{
			if ((script = dynamic_cast<Script*>(compo)))
			{
				script->OnStop();
				script = nullptr;
			}
		}
	}
	currentState = STATE_EXIT;
}

std::string		Stop::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
