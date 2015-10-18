#include "DOGLE.hpp"
#include "Script.hpp"

class MaClass : public Script
{
	public:

		MaClass(std::string n) : Script(n) {}



		void			Update()
		{
			//TMP
			if (Inputs::singleton->KeyPressed(KEY_A))
				transform->position += glm::vec3(0.05, 0, 0);
			if (Inputs::singleton->KeyPressed(KEY_D))
				transform->position -= glm::vec3(0.05, 0, 0);
			if (Inputs::singleton->KeyPressed(KEY_W))
				transform->position += glm::vec3(0.0, 0.0, 0.05);
			if (Inputs::singleton->KeyPressed(KEY_S))
				transform->position -= glm::vec3(0.0, 0.0, 0.05);
			if (Inputs::singleton->KeyPressed(KEY_SPACE))
				transform->position -= glm::vec3(0.0, 0.05, 0.0);
			if (Inputs::singleton->KeyPressed(KEY_CONTROL))
				transform->position += glm::vec3(0.0, 0.05, 0.0);
			// END TMP
		}

	private:

};
