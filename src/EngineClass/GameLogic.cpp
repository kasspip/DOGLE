#include "GameLogic.hpp"
#include "Script.hpp"

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
	
	std::list<GameObject*> GameObjects = app.GetCurrentScene()->GetGameObjectList();
	std::list<GameObject*>::iterator go = GameObjects.begin();
	
	Script* script = NULL;
	
	for (; go != GameObjects.end(); go++)
	{
		if ((script = (*go)->GetComponent<Script>()))
		{
			script->Update();
			script = NULL;
		}
	}
	currentState = STATE_RENDER;
}

std::string		GameLogic::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
