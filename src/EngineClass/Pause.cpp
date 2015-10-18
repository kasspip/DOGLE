#include "Pause.hpp"
#include "Script.hpp"

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
	(void)app;
	currentState = STATE_DESTROY;
}

std::string		Pause::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
