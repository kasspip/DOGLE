# include "DOGLE.hpp"
# include "Script.hpp"

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
			obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Player"));
			obj->name = "Player";

			obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("TextScore"));
			obj->name = "TextScore";

			obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("ChunkManager"));
			loadAssets = true;
		}
		else
			Destroy(gameObject);
	}

};
