#include "Start.hpp"

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
	app.LoadScene(app.GetCurrentScene());
	currentState = PHYSICS;
}

std::string		Start::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //



// GETTER SETTER //
