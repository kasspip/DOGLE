#include "StateMachine.hpp"

IState	*StateMachine::_states[] =
{
	new Initialisation
};

// CONSTRUCTOR DESTRUCTOR //

StateMachine::StateMachine(void) :	_currentState(INITIALISATION)
{

}

StateMachine::~StateMachine(void)
{

}

// OVERLOADS //

StateMachine	&StateMachine::operator=(StateMachine const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, StateMachine const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		StateMachine::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
