#include "Inputs.hpp"
#include "Script.hpp"

// STATIC //

Inputs*				Inputs::singleton = NULL;
key_event			Inputs::_key[KEY_COUNT];

// CONSTRUCTOR DESTRUCTOR //

Inputs::Inputs(void)
{
	singleton = this;
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
	glfwSetKeyCallback(app.window, _KeyCallback);
	app.appShouldClose = _key[KEY_ESC];
	currentState = STATE_GAMELOGIC;
}

bool			Inputs::KeyPressed(e_key key)
{
	return (_key[key] == KEY_EVENT_PRESSED);
}

bool			Inputs::KeyReleased(e_key key)
{
	return (_key[key] == KEY_EVENT_RELEASED);
}

std::string		Inputs::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

void			Inputs::_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	_key[KEY_ESC] = Inputs::_SetEvent(GLFW_KEY_ESCAPE, key, action);
	_key[KEY_W] = Inputs::_SetEvent(GLFW_KEY_W, key, action);
	_key[KEY_A] = Inputs::_SetEvent(GLFW_KEY_A, key, action);
	_key[KEY_S] = Inputs::_SetEvent(GLFW_KEY_S, key, action);
	_key[KEY_D] = Inputs::_SetEvent(GLFW_KEY_D, key, action);
	_key[KEY_SPACE] = Inputs::_SetEvent(GLFW_KEY_SPACE, key, action);
	_key[KEY_SHIFT] = Inputs::_SetEvent(GLFW_KEY_LEFT_SHIFT, key, action);
	_key[KEY_CONTROL] = Inputs::_SetEvent(GLFW_KEY_LEFT_CONTROL, key, action);

	if (_key[KEY_ESC] == true)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

key_event			Inputs::_SetEvent(int key_name, int key, int action)
{
		if (key == key_name && (action == GLFW_REPEAT || action == GLFW_PRESS))
			return KEY_EVENT_PRESSED;
		else if (key == key_name && action == GLFW_RELEASE)
			return KEY_EVENT_RELEASED;
		return KEY_EVENT_NONE;
}

// GETTER SETTER //
