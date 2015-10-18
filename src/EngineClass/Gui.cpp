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
	(void)app;
	currentState = STATE_PAUSING;
}

std::string		Gui::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
