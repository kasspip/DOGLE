# include "DOGLE.hpp"
# include "Script.hpp"

	class ControlCamera : public Script
	{
		GameObject* cube = NULL;

		public:

			ControlCamera() : Script("ControlCamera") {}

			void			Awake()
			{
				transform->position +=  glm::vec3(0,0,-3);
			}
	
			void			Update()
			{
				if (Inputs::singleton->KeyPressed(GLFW_KEY_A))
					transform->position += glm::vec3(0.05, 0, 0);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_D))
					transform->position -= glm::vec3(0.05, 0, 0);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_W))
					transform->position += glm::vec3(0.0, 0.0, 0.05);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_S))
					transform->position -= glm::vec3(0.0, 0.0, 0.05);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_SPACE))
					transform->position -= glm::vec3(0.0, 0.05, 0.0);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_LEFT_CONTROL))
					transform->position += glm::vec3(0.0, 0.05, 0.0);

				if (Inputs::singleton->KeyDown(GLFW_KEY_F))
					cube = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonCube"));
				if (cube && Inputs::singleton->KeyDown(GLFW_KEY_E))
				{
					Destroy(cube);
					cube = NULL;
				}
			}
	};
