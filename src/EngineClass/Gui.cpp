#include "Gui.hpp"
#include "Script.hpp"

// CONSTRUCTOR DESTRUCTOR //

Gui::Gui(void)
{

}

Gui::~Gui(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Gui const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Gui::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <GUI>");

	Script* script = nullptr;
	for (GameObject* go : app.GetCurrentScene()->GetGameObjectList())
	{
		if ((script = go->GetComponent<Script>()))
		{
			script->OnGUI();
			script = nullptr;
		}
	}

	currentState = STATE_PAUSE;
}

std::string		Gui::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
