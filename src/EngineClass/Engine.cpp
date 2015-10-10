#include "Engine.hpp"

// CONSTRUCTOR DESTRUCTOR //

Engine::Engine(Application &app) :	_app(app),
									_SM(app)
{}

Engine::~Engine(void)
{

}

// OVERLOADS //

Engine	&Engine::operator=(Engine const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Engine const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Engine::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
