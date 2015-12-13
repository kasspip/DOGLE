# include "DOGLE.hpp"
# include "Script.hpp"

#ifndef SCRIPTLOADINGPANEL
#define SCRIPTLOADINGPANEL


class ScriptLoadingPanel : public Script
{
	public:

	ScriptLoadingPanel() : Script("ScriptLoadingPanel") {}
	Script* Clone() { return new ScriptLoadingPanel(*this); }

	bool	loadAssets;

	void	Awake()
	{
		loadAssets = false;
	}
	
	void Update()
	{
		if (!loadAssets)
		{
			GameObject* obj;
			if (Application::singleton->playerChoice == 0)
			{
				obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("PlayerMarvin"));
				obj->name = "Player";
			}
			else if (Application::singleton->playerChoice == 1)
			{
				obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("PlayerRobot"));
				obj->name = "Player";
			}
			else if (Application::singleton->playerChoice == 2)
			{
				obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("PlayerFallout"));
				obj->name = "Player";
			}
			else
				std::cout << "error choice : " << Application::singleton->playerChoice << std::endl;
			
			obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("TextScore"));
			obj->name = "TextScore";

			obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("ChunkManager"));
			loadAssets = true;
		}
		else
			Destroy(gameObject);
	}

};

#endif

