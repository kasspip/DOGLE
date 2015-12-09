# include "DOGLE.hpp"
# include "Script.hpp"
# include <sstream>

class ScriptChangeText : public Script
{
	public:

	ScriptChangeText() : Script("ScriptChangeText") {}
	Script* Clone() { return new ScriptChangeText(*this); }

	Text *text;
	int score; 

	void	Awake()
	{
		score = 0;
		text = gameObject->GetComponent<Text>();
		if (!text)
			std::cout << "ERROR" << std::endl;
	}

	void	Update()
	{
		std::stringstream ss;

		ss << "Score: " << score;
		text->text = ss.str();
		score++;

		if(Inputs::singleton->KeyPressed(GLFW_KEY_LEFT))
		{
			text->color = glm::vec3(1,1,1);
		}
		if(Inputs::singleton->KeyPressed(GLFW_KEY_DOWN))
		{
			text->scale = 2;
		}
		if(Inputs::singleton->KeyPressed(GLFW_KEY_UP))
		{
			text->x = 25;
			text->y = 500;
		}

	}

};
