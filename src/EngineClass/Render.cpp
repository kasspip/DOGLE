#include "Render.hpp"
#include "Script.hpp"

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
	
	Engine::_currTime = glfwGetTime();
	if (Engine::_currTime > Engine::_lastTime + (1.0f / static_cast<double>(app.FPS)))
	{
		Engine::_lastTime = Engine::_currTime;
		_UpdateFpsCounter(app.name, app.window);
	
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, app.winW, app.winH);
		glUseProgram(app.shaderProgramDebug);
		GLint variableLocation;
	
		// setting camera
		Scene* scene = app.GetCurrentScene();
		GameObject* sceneCamera = Camera::GetMainCamera();
		if (sceneCamera)
		{
			Camera* camera = sceneCamera->GetComponent<Camera>();
			variableLocation = glGetUniformLocation(app.shaderProgramDebug, "View");
			glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr( camera->View() ));
			variableLocation = glGetUniformLocation(app.shaderProgramDebug, "Projection");
			glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr( camera->Projection(app.winW, app.winH) ));
		}
		else
			throw DError() << msg("No current camera in scene " + scene->name);
	
		// rendering Skins
		Transform* transform = nullptr;
		Skin* skin = nullptr;
		for (GameObject* go : scene->GetGameObjectList())
		{
			if (go == sceneCamera)
				continue ;
			if ((transform = go->GetComponent<Transform>()))
			{
    	   		variableLocation = glGetUniformLocation(app.shaderProgramDebug, "Transform");
    	    	glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(transform->GetMatrice()));
				transform = nullptr;
			}
			if ((skin = go->GetComponent<Skin>())
				&& skin->GetIsBind() == true)
			{
				glBindTexture(GL_TEXTURE_2D, skin->textureBind);
				glBindVertexArray(skin->vao);
				glDrawArrays(GL_TRIANGLES, 0, skin->nb_vertices);
				skin = nullptr;
			}
		}
		glfwSwapBuffers(app.window);
	}
	currentState = STATE_GUI;
}

std::string		Render::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

void 			Render::_UpdateFpsCounter (std::string & name, GLFWwindow* window)
{
	static double previous_seconds = glfwGetTime ();
	static int frame_count;
	
	double current_seconds = glfwGetTime ();
	double elapsed_seconds = current_seconds - previous_seconds;
	
	if (elapsed_seconds > 0.25)
	{
	  previous_seconds = current_seconds;
	  double fps = (double)frame_count / elapsed_seconds;
	  char tmp[128];
	  sprintf (tmp, "%s - fps: %.2f", name.c_str(), fps);
	  glfwSetWindowTitle (window, tmp);
	  frame_count = 0;
	}

	frame_count++;
}

// GETTER SETTER //
