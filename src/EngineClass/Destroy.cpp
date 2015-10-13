#include "Destroy.hpp"

// CONSTRUCTOR DESTRUCTOR //

Destroy::Destroy(void)
{

}

Destroy::~Destroy(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Destroy const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Destroy::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Destroy>");
	(void)app;
	if (app.appShouldClose == false)
		currentState = PHYSICS;
	else
		currentState = STOP;
}

std::string		Destroy::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
