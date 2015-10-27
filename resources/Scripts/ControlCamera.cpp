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
				obj = Application::singleton->GetCurrentScene()->FindGameObject("MonCube (3)");
				
			}

			void			Update()
			{
				Navigation();
				
				ChangeScene();
				PauseEngine();
				transform->position = obj->GetComponent<Transform>()->position + glm::vec3(0,0,5); 

				if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
				 	Application::singleton->Stop();
				if (Inputs::singleton->KeyDown(GLFW_KEY_Q))
					Application::singleton->Save();
			}

			void			Navigation()
			{
				if(Inputs::singleton->KeyPressed(GLFW_KEY_W))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveZ(5);
        		if(Inputs::singleton->KeyPressed(GLFW_KEY_S))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveZ(-5);
    			if(Inputs::singleton->KeyPressed(GLFW_KEY_D))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveX(5);
    			if(Inputs::singleton->KeyPressed(GLFW_KEY_A))
        			Camera::GetMainCamera()->GetComponent<Camera>()->MoveX(-5);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_R))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation += glm::vec3(0.5,0,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_F))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation -= glm::vec3(0.5,0,0);

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
