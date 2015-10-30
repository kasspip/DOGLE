#include "DOGLE.hpp"
#include "Script.hpp"

class MyCube : public Script
{
	public:

		GameObject* child = nullptr;
		float 		baseSpeed = 3;


		MyCube() : Script("MyCube") {}
		Script* 		Clone() { return new MyCube(*this); }

		// void			Awake()
		// {
		// 	child = Application::singleton->GetCurrentScene()->InstanciatePrefab(
		// 	 		Application::singleton->FindPrefab("child"));

		// 	child->GetComponent<Transform>()->position += glm::vec3(1.5,0,0);
		// 	child->SetParent(gameObject);
			
		// 	//Camera::GetMainCamera()->SetParent(gameObject);
		// }

		void			Update()
		{

		 	float speed = (baseSpeed * Engine::singleton->deltaTime);
			
		// 	//transform->rotation += glm::vec3(0,0.005,0.001);
			
			if (Inputs::singleton->KeyPressed(GLFW_KEY_I))
				transform->position -= glm::vec3(0.0, 0.0, speed);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_K))
				transform->position += glm::vec3(0.0, 0.0, speed);

			if (Inputs::singleton->KeyPressed(GLFW_KEY_J))
				transform->position -= glm::vec3(speed, 0, 0);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_L))
				transform->position += glm::vec3(speed, 0, 0);


		}


	private:

		// void			PopObj()
		// {
		// 	if (!obj && Inputs::singleton->KeyDown(GLFW_KEY_E))
		// 		obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonTriangle"), *transform);
		// }

		// void			RemoveObj()
		// {
		// 	if (obj && Inputs::singleton->KeyDown(GLFW_KEY_R))
		// 	{
		// 		Destroy(obj);
		// 		obj = nullptr;
		// 	}
		// }
};
