#include "Inputs.hpp"
#include "Script.hpp"

#define KEY_DOWN -5

// STATIC //

Inputs*				Inputs::singleton = NULL;
int					Inputs::_key[GLFW_KEY_LAST];

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
	KeyState(app.window, GLFW_KEY_ESCAPE);
	KeyState(app.window, GLFW_KEY_Q);
	KeyState(app.window, GLFW_KEY_W);
	KeyState(app.window, GLFW_KEY_E);
	KeyState(app.window, GLFW_KEY_R);

	KeyState(app.window, GLFW_KEY_A);
	KeyState(app.window, GLFW_KEY_S);
	KeyState(app.window, GLFW_KEY_D);
	KeyState(app.window, GLFW_KEY_F);


	
	KeyState(app.window, GLFW_KEY_SPACE);
	KeyState(app.window, GLFW_KEY_LEFT_SHIFT);
	KeyState(app.window, GLFW_KEY_LEFT_CONTROL);
	if (KeyPressed(GLFW_KEY_ESCAPE))
		app.appShouldClose = GL_TRUE;
	if (_key[GLFW_KEY_ESCAPE] == GL_TRUE)
		glfwSetWindowShouldClose(app.window, GL_TRUE);
	currentState = STATE_GAMELOGIC;
}

bool			Inputs::KeyPressed(int key)
{
	return (_key[key] == GLFW_PRESS || _key[key] == KEY_DOWN);
}

bool			Inputs::KeyDown(int key)
{
	return (_key[key] == KEY_DOWN);
}

bool			Inputs::KeyReleased(int key)
{
	return (_key[key] == GLFW_RELEASE);
}

std::string		Inputs::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void			Inputs::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)scancode;
	(void)action;
	(void)mods;
	(void)key;
}

// PRIVATE //

void		Inputs::KeyState(GLFWwindow *window, int id)
{
	int		ret = 0;

	if ((ret = glfwGetKey(window, id)) == GLFW_PRESS && (_key[id] != GLFW_PRESS && _key[id] != KEY_DOWN))
		_key[id] = KEY_DOWN;
	else
		_key[id] = ret;
}

// GETTER SETTER //
