# include "DOGLE.hpp"
# include "Script.hpp"
# include "ScriptControlPlayer.cpp"

class ScriptObstacle : public Script
{
	public:

	ScriptObstacle() : Script("ScriptObstacle") {}
	Script* Clone() { return new ScriptObstacle(*this); }


	std::vector<std::string>	little_obs = {"Obstacle2"};
	GameObject *visual;
	GameObject *player = nullptr;
	Transform *playerTrans = nullptr;

	void 	Awake ()
	{
		visual = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab(
				little_obs[rand() % little_obs.size()] 
				));
		float rand_rot = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2 * M_PI));
		visual->GetComponent<Transform>()->SetPosition(transform->_position);
		visual->GetComponent<Transform>()->SetRotation(glm::vec3(0, rand_rot, 0));
	}

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

	void OnDestroy()
	{
		Destroy(visual);
	}

};
