# include "DOGLE.hpp"
# include "Script.hpp"

class ScriptCoffee : public Script
{
	public:

	ScriptCoffee() : Script("ScriptCoffee") {}
	Script* Clone() { return new ScriptCoffee(*this); }

	void		Awake()
	{
		transform->SetPosition(transform->_position.x, 1, transform->_position.z);
		transform->SetRotation(0.2, 0, 0.2);
	}

	void		Update()
	{
		glm::vec3 newRot = glm::vec3 (transform->_rotation.x, transform->_rotation.y + 5 * Engine::singleton->deltaTime, transform->_rotation.z);
		transform->SetRotation( newRot );
	}

};
