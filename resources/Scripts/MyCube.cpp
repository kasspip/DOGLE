#include "DOGLE.hpp"
#include "Script.hpp"

class MyCube : public Script
{
	public:

			GameObject* obj = nullptr;


		MyCube() : Script("MyCube") {}
		Script* 		Clone() { return new MyCube(*this); }

		void			OnDestroy()
		{
			std::cout << " OnDestroy() " << name << " says Boom !" << std::endl;
		}

		void			Update()
		{
			//transform->rotation += glm::vec3(0, 0.002, 0);
			PopObj();
			RemoveObj();

			if (Inputs::singleton->KeyPressed(GLFW_KEY_J))
				transform->position -= glm::vec3(0.05, 0, 0);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_L))
				transform->position += glm::vec3(0.05, 0, 0);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_I))
				transform->position += glm::vec3(0.0, 0.0, 0.05);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_K))
				transform->position -= glm::vec3(0.0, 0.0, 0.05);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_SPACE))
				transform->position += glm::vec3(0.0, 0.05, 0.0);
			if (Inputs::singleton->KeyPressed(GLFW_KEY_LEFT_CONTROL))
				transform->position -= glm::vec3(0.0, 0.05, 0.0);
		}

		void			PopObj()
		{
			if (!obj && Inputs::singleton->KeyDown(GLFW_KEY_E))
				obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonTriangle"), *transform);
		}

		void			RemoveObj()
		{
			if (obj && Inputs::singleton->KeyDown(GLFW_KEY_R))
			{
				Destroy(obj);
				obj = nullptr;
			}
		}

		void			OnStop()
		{
			std::cout << "script OnStop() " << std::endl;
		}
	private:

};
