#include "Physics.hpp"

// CONSTRUCTOR DESTRUCTOR //

Physics::Physics(void)
{

}

Physics::~Physics(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Physics const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Physics::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Physics>");
	(void)app;
	currentState = INPUTS;
}

std::string		Physics::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
