#include "Render.hpp"
#include "Script.hpp"

// CONSTRUCTOR DESTRUCTOR //

Render::Render(void)
{
	_scene = nullptr;
	_sceneCamera = nullptr;
	_variableLocation = 0;
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
		
		if (_scene == nullptr || _scene != app.GetCurrentScene())
		{
			_scene = app.GetCurrentScene();
			_sceneCamera = Camera::GetMainCamera();
			_SetupLights();
		}

		_RenderGameObjects(app);

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

void			Render::_SetupLights()
{
	Light* light = nullptr;

	_lights.clear();

	for (GameObject* go : _scene->GetGameObjectList())
	{
		if ((light = go->GetComponent<Light>()) != nullptr)
			_lights.push_back(light);
	}
}


void			Render::_RenderGameObjects(Application & app)
{
	Transform* transform = nullptr;
	Skin* skin = nullptr;

	for (GameObject* go : _scene->GetGameObjectList())
	{

		if (go == _sceneCamera)
			continue ;

		if ((transform = go->GetComponent<Transform>()))
		{
			if (go->GetComponent<Light>()) // gizmo render
			{
				glUseProgram(app.shaderProgram_Gizmo);
				_SetupCamera(app);
				_variableLocation = glGetUniformLocation(app.shaderProgram_Gizmo, "Transform");
				glUniformMatrix4fv(_variableLocation, 1, GL_FALSE, glm::value_ptr(transform->GetMatrice()));
			}
			else //standard render
			{
				glUseProgram(app.shaderProgram_Standard);
				_SetupCamera(app);
				_variableLocation = glGetUniformLocation(app.shaderProgram_Standard, "Transform");
				glUniformMatrix4fv(_variableLocation, 1, GL_FALSE, glm::value_ptr(transform->GetMatrice()));
				
				for (Light *light : _lights)
				{
					_variableLocation = glGetUniformLocation(app.shaderProgram_Standard, "lightPosition");
					glUniform3f(_variableLocation, 	light->transform->_position.x, 
													light->transform->_position.y, 
													light->transform->_position.z);
					_variableLocation  = glGetUniformLocation(app.shaderProgram_Standard, "light.ambient");
					glUniform3f(_variableLocation,  0.2f, 0.2f, 0.2f);
					_variableLocation  = glGetUniformLocation(app.shaderProgram_Standard, "light.diffuse");
					glUniform3f(_variableLocation,  light->color.x, light->color.y, light->color.z);
					_variableLocation = glGetUniformLocation(app.shaderProgram_Standard, "light.specular");
					glUniform3f(_variableLocation, 1.0f, 1.0f, 1.0f);
				}
			}

			transform = nullptr;
		}

		if ((skin = go->GetComponent<Skin>()) && skin->GetIsBind() == true)
		{
			_variableLocation  = glGetUniformLocation(app.shaderProgram_Standard, "material.ambient");
			glUniform3f(_variableLocation, skin->ambient.r, skin->ambient.g, skin->ambient.b);
			_variableLocation  = glGetUniformLocation(app.shaderProgram_Standard, "material.diffuse");
			glUniform3f(_variableLocation, skin->diffuse.r, skin->diffuse.g, skin->diffuse.b);
			_variableLocation = glGetUniformLocation(app.shaderProgram_Standard, "material.specular");
			glUniform3f(_variableLocation, skin->specular.r, skin->specular.g, skin->specular.b);
			_variableLocation    = glGetUniformLocation(app.shaderProgram_Standard, "material.shininess"); 			
			glUniform1f(_variableLocation, 64.0f);

			glBindTexture(GL_TEXTURE_2D, skin->textureBind);
			glBindVertexArray(skin->vao);
			glDrawArrays(GL_TRIANGLES, 0, skin->nb_vertices);
			skin = nullptr;
		}
	}
}


void			Render::_SetupCamera(Application & app)
{
	if (_sceneCamera)
	{
		Camera* camera = _sceneCamera->GetComponent<Camera>();
		
		// gizmo render
		_variableLocation = glGetUniformLocation(app.shaderProgram_Gizmo, "View");
		glUniformMatrix4fv(_variableLocation, 1, GL_FALSE, glm::value_ptr( camera->View() ));
		_variableLocation = glGetUniformLocation(app.shaderProgram_Gizmo, "Projection");
		glUniformMatrix4fv(_variableLocation, 1, GL_FALSE, glm::value_ptr( camera->Projection(app.winW, app.winH) ));

		//standard render
		_variableLocation = glGetUniformLocation(app.shaderProgram_Standard, "View");
		glUniformMatrix4fv(_variableLocation, 1, GL_FALSE, glm::value_ptr( camera->View() ));
		_variableLocation = glGetUniformLocation(app.shaderProgram_Standard, "Projection");
		glUniformMatrix4fv(_variableLocation, 1, GL_FALSE, glm::value_ptr( camera->Projection(app.winW, app.winH) ));
		GLint viewPosLoc = glGetUniformLocation(app.shaderProgram_Standard, "viewPosition");
		glUniform3f(viewPosLoc, camera->transform->_position.x, 
								camera->transform->_position.y, 
								camera->transform->_position.z);
	}
	else
		throw DError() << msg("No current camera in _scene " + _scene->name);
}


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
