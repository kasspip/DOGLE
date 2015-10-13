#include "Inputs.hpp"

bool			Inputs::_key[] = {false};

void			Inputs::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	_key[KEY_ESC] = Inputs::EventPressed(GLFW_KEY_ESCAPE, key, action);
	if (_key[KEY_ESC] == true)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool			Inputs::EventPressed(int key_name, int key, int action)
{
	if (key == key_name && (action == GLFW_REPEAT || action == GLFW_PRESS))
		return (true);
	return (false);
}

// CONSTRUCTOR DESTRUCTOR //

Inputs::Inputs(void)
{
}

Inputs::~Inputs(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Inputs const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Inputs::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Inputs>");
	glfwPollEvents();
	glfwSetKeyCallback(app.window, KeyCallback);
	app.appShouldClose = _key[KEY_ESC];
	currentState = GAMELOGIC;
}

bool			Inputs::KeyIsPressed(e_key key)
{
	return _key[key];
}


std::string		Inputs::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //



// GETTER SETTER //
