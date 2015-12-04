# include "DOGLE.hpp"
# include "Script.hpp"

class ScriptChunkSpawner : public Script
{
	public:
	GameObject*	chunk = nullptr;
	GameObject*	chunk2 = nullptr;
	ScriptChunkSpawner() : Script("ScriptChunkSpawner") {}
	Script* Clone() { return new ScriptChunkSpawner(*this); }

	void			Awake()
	{
		if (!chunk)
			chunk = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("chunk0"));
		if (!chunk2)
			chunk2 = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("chunk0"));
	}

	void	Update()
	{

	}
};
