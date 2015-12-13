# include "DOGLE.hpp"
# include "Script.hpp"

class ScriptMenu : public Script
{
	public:

	ScriptMenu() : Script("ScriptMenu") {}
	Script* Clone() { return new ScriptMenu(*this); }

	std::list<GameObject*> players;

	unsigned long	currChoice = 0;

	void		Awake()
	{
		players.push_back(Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Choice1")));
		players.push_back(Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Choice2")));		
		players.push_back(Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Choice3")));		
	}

	void		Update()
	{
			if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
				Application::singleton->Stop();
			else if (Inputs::singleton->KeyDown(GLFW_KEY_SPACE))
				Application::singleton->LoadScene("GameScene");

			if (Inputs::singleton->KeyDown(GLFW_KEY_A) && currChoice > 0)
			{
				for (GameObject* go : players)
				{
					Transform* trans = go->GetComponent<Transform>();
					trans->SetPosition(trans->_position + glm::vec3(10,0,0));
				}
				currChoice -= 1;
				Application::singleton->playerChoice = currChoice;
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_D) && currChoice < players.size() - 1)
			{
				for (GameObject* go : players)
				{
					Transform* trans = go->GetComponent<Transform>();
					trans->SetPosition(trans->_position + glm::vec3(-10,0,0));
				}
				currChoice += 1;
				Application::singleton->playerChoice = currChoice;
			}
	}
};
