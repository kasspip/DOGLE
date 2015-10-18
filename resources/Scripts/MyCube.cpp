#include "DOGLE.hpp"
#include "Script.hpp"

class MyCube : public Script
{
	public:

		MyCube() : Script("MyCube") {}

		void			Awake()
		{
			Camera::GetMainCamera()->GetComponent<Camera>()->transform->position = transform->position + glm::vec3(0,0,-3);
		}


	private:

};
