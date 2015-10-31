#include "Physics.hpp"
#include "Script.hpp"
#include "Engine.hpp"

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
	(void)app;

	float currentFrame = glfwGetTime();
	Engine::singleton->deltaTime = currentFrame - Engine::singleton->lastFrame;
	Engine::singleton->lastFrame = currentFrame; 

	Script* script = nullptr;
	for (GameObject* go : app.GetCurrentScene()->GetGameObjectList())
	{
		for (IComponent* compo : go->GetListComponent())
		{
			if ((script = dynamic_cast<Script*>(compo)))
			{
				script->OnCollisionEnter(5);
				script = nullptr;
			}
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
