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

	std::list<GameObject*> GameObjects = app.GetCurrentScene()->GetGameObjectList();
	std::list<GameObject*>::iterator go = GameObjects.begin();
	
	Transform* transform = NULL;
	
	for (; go != GameObjects.end(); go++)
	{
		if ((transform = (*go)->GetComponent<Transform>()))
		{
        	transform->CalculateTransform();
			transform = NULL;
		}
	}
	currentState = STATE_INPUTS;
}

std::string		Physics::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
