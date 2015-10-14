#include "GameLogic.hpp"

// CONSTRUCTOR DESTRUCTOR //

GameLogic::GameLogic(void)
{

}

GameLogic::~GameLogic(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, GameLogic const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			GameLogic::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <GameLogic>");
	(void)app;
	currentState = STATE_RENDER;
}

std::string		GameLogic::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
