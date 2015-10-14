#include "Render.hpp"

// CONSTRUCTOR DESTRUCTOR //

Render::Render(void)
{

}

Render::~Render(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Render const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Render::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Render>");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, app.winW, app.winH);

	std::list<GameObject*> GameObjects = app.GetCurrentScene()->GetGameObjectList();
	std::list<GameObject*>::iterator go = GameObjects.begin();

	Skin* skin = NULL;
	glUseProgram(app.shaderProgramDebug);
	for (; go != GameObjects.end(); go++)
	{
		if ((skin = (*go)->GetComponent<Skin>())
			&& skin->GetIsBind() == true)
		{
			glBindVertexArray(skin->vao);
			glDrawArrays(GL_TRIANGLES, 0, skin->nb_vertices);
			skin = NULL;
		}
	}
	glfwSwapBuffers(app.window);
	currentState = STATE_GUI;
}

std::string		Render::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //


// GETTER SETTER //
