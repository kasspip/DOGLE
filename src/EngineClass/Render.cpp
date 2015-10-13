#include "Render.hpp"

// CONSTRUCTOR DESTRUCTOR //

Render::Render(void)
{

}

Render::~Render(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Render const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Render::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Render>");
	(void)app;
	currentState = GUI;
}

std::string		Render::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
