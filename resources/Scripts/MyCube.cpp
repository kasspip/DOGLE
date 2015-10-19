#include "DOGLE.hpp"
#include "Script.hpp"

class MyCube : public Script
{
	public:

		MyCube() : Script("MyCube") {}

		void			Awake()
		{
			transform->position = (Camera::GetMainCamera()->GetComponent<Camera>()->transform->position * glm::vec3(-1,-1,-1)) + glm::vec3(0,0,-2);
		}



		void			OnDestroy()
		{
			std::cout << "Boom !" << name << std::endl;
		}

	private:

};
