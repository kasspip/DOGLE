# include "DOGLE.hpp"
# include "Script.hpp"
# include "ScriptControlPlayer.cpp"

class ScriptObstacle : public Script
{
	public:

	ScriptObstacle() : Script("ScriptObstacle") {}
	Script* Clone() { return new ScriptObstacle(*this); }



	GameObject *player = nullptr;
	Transform *playerTrans = nullptr;

	void Update()
	{
		if (!player)
		{
			player = Application::singleton->GetCurrentScene()->FindGameObject("Player");
			playerTrans = player->GetComponent<Transform>();
		}
		if (glm::distance(playerTrans->_position, transform->_position) < 1)
		{
			ScriptControlPlayer	*script = dynamic_cast<ScriptControlPlayer *>(player->GetComponent<Script>());
			script->isDead = true;
		}
	}

};
