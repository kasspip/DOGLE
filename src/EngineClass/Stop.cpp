#include "Stop.hpp"

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
	(void)app;
	currentState = STATE_EXIT;
}

std::string		Stop::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
