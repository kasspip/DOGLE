# include "DOGLE.hpp"
# include "Script.hpp"

	class ControlCamera : public Script
	{

		public:
			GameObject*	obj = nullptr;
			Camera*		camera = nullptr;

			ControlCamera() : Script("ControlCamera") {}
			Script* Clone() { return new ControlCamera(*this); }

			void			Awake()
			{
				transform->position =  glm::vec3(0,0,3);
				if (Application::singleton->GetCurrentScene()->name == "Level1")
					obj = Application::singleton->GetCurrentScene()->FindGameObject("MonCube (3)");
			}

			void			Update()
			{
				Navigation();
				ChangeScene();
				PauseEngine();
				
				if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
				 	Application::singleton->Stop();
				if (Inputs::singleton->KeyDown(GLFW_KEY_Q))
					Application::singleton->Save();
			}

			void			Navigation()
			{
				if(Inputs::singleton->KeyPressed(GLFW_KEY_W))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveZ(3);
        		if(Inputs::singleton->KeyPressed(GLFW_KEY_S))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveZ(-3);
    			if(Inputs::singleton->KeyPressed(GLFW_KEY_D))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveX(3);
    			if(Inputs::singleton->KeyPressed(GLFW_KEY_A))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveX(-3);
							if (Inputs::singleton->KeyPressed(GLFW_KEY_SPACE))
				transform->position += glm::vec3(0.0, 0.05, 0.0);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_LEFT_CONTROL))
				transform->position -= glm::vec3(0.0, 0.05, 0.0);

				
				if(Inputs::singleton->KeyPressed(GLFW_KEY_UP))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation += glm::vec3(0.5,0,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_DOWN))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation -= glm::vec3(0.5,0,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_LEFT))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation -= glm::vec3(0,0.5,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_RIGHT))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation += glm::vec3(0,0.5,0);
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

			void		PauseEngine()
			{
				if (Inputs::singleton->KeyDown(GLFW_KEY_P))
					Engine::singleton->Pause();
			}
	};
