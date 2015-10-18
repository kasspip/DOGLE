#include "Inputs.hpp"
#include "Script.hpp"

// STATIC //

Inputs*				Inputs::singleton = NULL;
int					Inputs::_key[KEY_COUNT];

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
	return (_key[key] == GLFW_PRESS);
}

bool			Inputs::KeyReleased(e_key key)
{
	return (_key[key] == GLFW_RELEASE);
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
	(void)action;
	(void)mods;
	(void)key;
	_key[KEY_ESC] = glfwGetKey(window, GLFW_KEY_ESCAPE);
	_key[KEY_W] = glfwGetKey(window, GLFW_KEY_W);
	_key[KEY_A] = glfwGetKey(window, GLFW_KEY_A);
	_key[KEY_S] = glfwGetKey(window, GLFW_KEY_S);
	_key[KEY_D] = glfwGetKey(window, GLFW_KEY_D);
	_key[KEY_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE);
	_key[KEY_SHIFT] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
	_key[KEY_CONTROL] = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);

	if (_key[KEY_ESC] == true)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// GETTER SETTER //
