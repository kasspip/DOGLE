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
	GLint variableLocation;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, app.winW, app.winH);
	glUseProgram(app.shaderProgramDebug);


	Scene* scene = app.GetCurrentScene();
	
	// setting camera
	GameObject* sceneCamera = scene->GetCurrentCamera();
	if (sceneCamera)
	{
		Transform* transform = sceneCamera->GetComponent<Transform>();


		//TMP
       		if (KeyIsPressed(KEY_A))
       			transform->position += glm::vec3(0.05, 0, 0);
       		if (KeyIsPressed(KEY_D))
       			transform->position -= glm::vec3(0.05, 0, 0);
       		if (KeyIsPressed(KEY_W))
       			transform->position += glm::vec3(0.0, 0.0, 0.05);
       		if (KeyIsPressed(KEY_S))
       			transform->position -= glm::vec3(0.0, 0.0, 0.05);
       		if (KeyIsPressed(KEY_SPACE))
       			transform->position -= glm::vec3(0.0, 0.05, 0.0);
       		if (KeyIsPressed(KEY_CONTROL))
       			transform->position += glm::vec3(0.0, 0.05, 0.0);

		variableLocation = glGetUniformLocation(app.shaderProgramDebug, "View");
		glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr( transform->GetTransform() ));
		Camera* camera = sceneCamera->GetComponent<Camera>();
		variableLocation = glGetUniformLocation(app.shaderProgramDebug, "Projection");
		glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr( camera->GetProjection(app.winW, app.winH) ));
	}
	else
		throw DError() << msg("No current camera in scene " + scene->name);


	// rendering Skins
	std::list<GameObject*> GameObjects = scene->GetGameObjectList();
	std::list<GameObject*>::iterator go = GameObjects.begin();
	Transform* transform = NULL;
	Skin* skin = NULL;
	for (; go != GameObjects.end(); go++)
	{
		if (*go == sceneCamera)
			continue ;
		if ((transform = (*go)->GetComponent<Transform>()))
		{
       		transform->position = glm::vec3(0, 0, -3); // TMP

       		transform->rotation += glm::vec3(0, 0.04, 0); // TMP
       		variableLocation = glGetUniformLocation(app.shaderProgramDebug, "Transform");
        	glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(transform->GetTransform()));
			transform = NULL;
		}
		if ((skin = (*go)->GetComponent<Skin>())
			&& skin->GetIsBind() == true)
		{

			glBindTexture(GL_TEXTURE_2D, skin->textureBind);
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
