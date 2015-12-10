# include "DOGLE.hpp"
# include "Script.hpp"

class ScriptMenu : public Script
{
	public:

	ScriptMenu() : Script("ScriptMenu") {}
	Script* Clone() { return new ScriptMenu(*this); }

	void		Update()
	{
			if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
				Application::singleton->Stop();
			else if (Inputs::singleton->KeyDown(GLFW_KEY_SPACE))
				Application::singleton->LoadScene("GameScene");
	}

};
