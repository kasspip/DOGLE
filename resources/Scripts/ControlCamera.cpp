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
				Navigation();
				PopCube();
				RemoveCube();
				ChangeScene();
			}

			void			Navigation()
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
			}

			void			PopCube()
			{
				if (!cube && Inputs::singleton->KeyDown(GLFW_KEY_E))
					cube = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonCube"));
			}

			void			RemoveCube()
			{
				if (cube && Inputs::singleton->KeyDown(GLFW_KEY_R))
				{
					Destroy(cube);
					cube = NULL;
				}
			}

			void			ChangeScene()
			{
				if (Inputs::singleton->KeyDown(GLFW_KEY_F))
				{
					if (Application::singleton->GetCurrentScene()->name == "Level1")
						
						Application::singleton->LoadScene("Level2");
					else
						Application::singleton->LoadScene("Level1");
				}
			}
	};
