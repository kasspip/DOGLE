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
	if (app.appShouldClose == true || glfwWindowShouldClose (app.window))
		currentState = STATE_STOP;
	else
		currentState = STATE_PHYSICS;
}

std::string		Destroy::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
