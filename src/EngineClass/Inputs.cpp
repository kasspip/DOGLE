#include "Inputs.hpp"
#include "Script.hpp"

#define KEY_DOWN -5

// STATIC //

Inputs*				Inputs::singleton = nullptr;
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
	KeyState(app.window, GLFW_KEY_T);
	KeyState(app.window, GLFW_KEY_Y);
	KeyState(app.window, GLFW_KEY_U);
	KeyState(app.window, GLFW_KEY_I);
	KeyState(app.window, GLFW_KEY_O);
	KeyState(app.window, GLFW_KEY_P);

	KeyState(app.window, GLFW_KEY_A);
	KeyState(app.window, GLFW_KEY_S);
	KeyState(app.window, GLFW_KEY_D);
	KeyState(app.window, GLFW_KEY_F);
	KeyState(app.window, GLFW_KEY_G);
	KeyState(app.window, GLFW_KEY_H);
	KeyState(app.window, GLFW_KEY_J);
	KeyState(app.window, GLFW_KEY_K);
	KeyState(app.window, GLFW_KEY_L);
	
	KeyState(app.window, GLFW_KEY_Z);
	KeyState(app.window, GLFW_KEY_X);
	KeyState(app.window, GLFW_KEY_C);
	KeyState(app.window, GLFW_KEY_V);
	KeyState(app.window, GLFW_KEY_B);
	KeyState(app.window, GLFW_KEY_N);
	KeyState(app.window, GLFW_KEY_M);
	
	KeyState(app.window, GLFW_KEY_TAB);
	KeyState(app.window, GLFW_KEY_ENTER);
	KeyState(app.window, GLFW_KEY_SPACE);
	KeyState(app.window, GLFW_KEY_LEFT_SHIFT);
	KeyState(app.window, GLFW_KEY_LEFT_CONTROL);
	
	if (Engine::singleton->pause == true && KeyPressed(GLFW_KEY_ENTER))
		Engine::singleton->pause = false;
	else
		(Engine::singleton->pause == false) ? currentState = STATE_GAMELOGIC : currentState = STATE_PAUSE ;
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
