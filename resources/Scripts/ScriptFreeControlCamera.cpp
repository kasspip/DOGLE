# include "DOGLE.hpp"
# include "Script.hpp"

class ScriptFreeControlCamera : public Script
{
	public:

	ScriptFreeControlCamera() : Script("ScriptFreeControlCamera") {}
	Script* Clone() { return new ScriptFreeControlCamera(*this); }

	void Update()
	{
		Navigation();
	}

	void			Navigation()
	{
		float speed = (3 * Engine::singleton->deltaTime);

		if(Inputs::singleton->KeyPressed(GLFW_KEY_W))
			transform->_position -= glm::vec3(0, 0, speed * 2);
		if(Inputs::singleton->KeyPressed(GLFW_KEY_S))
			transform->_position += glm::vec3(0, 0, speed * 2);
		if(Inputs::singleton->KeyPressed(GLFW_KEY_D))
			transform->_position += glm::vec3(speed * 2, 0, 0);
		if(Inputs::singleton->KeyPressed(GLFW_KEY_A))
			transform->_position -= glm::vec3(speed * 2, 0, 0);
		if (Inputs::singleton->KeyPressed(GLFW_KEY_SPACE))
			transform->_position += glm::vec3(0.0, speed * 2, 0.0);
		if (Inputs::singleton->KeyPressed(GLFW_KEY_LEFT_CONTROL))
			transform->_position -= glm::vec3(0.0, speed * 2, 0.0);
		
				
		// if(Inputs::singleton->KeyPressed(GLFW_KEY_UP))
		// 	Camera::GetMainCamera()->GetComponent<Transform>()->_rotation += glm::vec3(speed,0,0);
		// if(Inputs::singleton->KeyPressed(GLFW_KEY_DOWN))
		// 	Camera::GetMainCamera()->GetComponent<Transform>()->_rotation -= glm::vec3(speed,0,0);
		// if(Inputs::singleton->KeyPressed(GLFW_KEY_LEFT))
		// 	Camera::GetMainCamera()->GetComponent<Transform>()->_rotation -= glm::vec3(0,speed,0);
		// if(Inputs::singleton->KeyPressed(GLFW_KEY_RIGHT))
		// 	Camera::GetMainCamera()->GetComponent<Transform>()->_rotation += glm::vec3(0,speed,0);
	}

};
