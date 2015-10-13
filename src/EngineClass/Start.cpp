#include "Start.hpp"

// CONSTRUCTOR DESTRUCTOR //

Start::Start(void)
{
}

Start::Start(Start const & src)
{
	*this = src;
}

Start::~Start(void)
{
}

// OVERLOADS //

Start	&Start::operator=(Start const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Start const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Start::RunState(Application & app, e_state & currentState)
{
	std::cout << "[MACHINE] <Start>" << std::endl;
	app.LoadScene(app.GetCurrentScene());
	currentState = EXIT;
}

std::string		Start::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //



// GETTER SETTER //
