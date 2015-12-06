#include "Destroy.hpp"
#include "Script.hpp"

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
	Script				*script = nullptr;
	std::list<GameObject*>	&list = app.GetCurrentScene()->GetGameObjectList();
	std::list<GameObject*>::iterator it = list.begin();
	for (; it != list.end(); ++it)
	{
		if ((*it)->GetDestroy() == true)
		{
			if ((script = (*it)->GetComponent<Script>()))
			{
				PRINT_DEBUG("Calling Destroy() from " + (*it)->name);
				std::cout << ("Calling Destroy() from " + (*it)->name) << std::endl;
				script->OnDestroy();
				script = nullptr;
			}
			delete *it;
			it = list.erase(it);
		}
	}

	if (app.GetStop() == true || glfwWindowShouldClose (app.window))
		currentState = STATE_STOP;
	else
		currentState = STATE_START;
}

std::string		Destroy::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
