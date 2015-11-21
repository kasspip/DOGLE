# include "DOGLE.hpp"
# include "Script.hpp"

	class ControlCamera : public Script
	{

		public:
			GameObject*	obj = nullptr;
			Camera*		camera = nullptr;
			float 		baseSpeed = 3;

			ControlCamera() : Script("ControlCamera") {}
			Script* Clone() { return new ControlCamera(*this); }

			void			Awake()
			{
				//transform->SetPosition(0,0,3);
			}

			void			Update()
			{
				Navigation();
				ChangeScene();
				PauseEngine();
				PopObj();
				RemoveObj();


				if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
				 	Application::singleton->Stop();
				if (Inputs::singleton->KeyDown(GLFW_KEY_Q))
					Application::singleton->Save();
			}

			void			Navigation()
			{
				//float speed = (baseSpeed * Engine::singleton->deltaTime);

				/*if(Inputs::singleton->KeyPressed(GLFW_KEY_W))
					transform->position -= glm::vec3(0, 0, speed);
        		if(Inputs::singleton->KeyPressed(GLFW_KEY_S))
					transform->position += glm::vec3(0, 0, speed);
    			if(Inputs::singleton->KeyPressed(GLFW_KEY_D))
					transform->position += glm::vec3(speed, 0, 0);
        		if(Inputs::singleton->KeyPressed(GLFW_KEY_A))
					transform->position -= glm::vec3(speed, 0, 0);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_SPACE))
					transform->position += glm::vec3(0.0, speed, 0.0);
				if (Inputs::singleton->KeyPressed(GLFW_KEY_LEFT_CONTROL))
					transform->position -= glm::vec3(0.0, speed, 0.0);
*/
				
			/*	if(Inputs::singleton->KeyPressed(GLFW_KEY_UP))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation += glm::vec3(speed * 3,0,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_DOWN))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation -= glm::vec3(speed * 3,0,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_LEFT))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation -= glm::vec3(0,speed * 3,0);
				if(Inputs::singleton->KeyPressed(GLFW_KEY_RIGHT))
					Camera::GetMainCamera()->GetComponent<Transform>()->rotation += glm::vec3(0,speed * 3,0);*/
			}

			void			PopObj()
			{
				if (!obj && Inputs::singleton->KeyDown(GLFW_KEY_E))
					obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonCube"), *transform);
			}
	
			void			RemoveObj()
			{
				if (obj && Inputs::singleton->KeyDown(GLFW_KEY_R))
				{
					Destroy(obj);
					obj = nullptr;
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

			void		PauseEngine()
			{
				if (Inputs::singleton->KeyDown(GLFW_KEY_P))
					Engine::singleton->Pause();
			}
	};
