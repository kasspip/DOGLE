# include "DOGLE.hpp"
# include "Script.hpp"
# include "ScriptControlPlayer.cpp"


enum BasicCard
{
	N = 0,
	O,
	S,
	E
};

class BasicDir
{
	public:
	

	BasicCard	card;
	glm::vec3	add;
	glm::vec3	rot;

	static	BasicCard	AddCard(BasicCard cur, int add)
	{
		int	i = static_cast<int>(cur);
		std::cout << "old i " << i << std::endl;
		i += add;
		if (i > 3)
			i = 0;
		else if (i < 0)
			i = 3;
		return (static_cast<BasicCard>(i));
	}


	BasicDir(BasicCard c)
	{
		std::cout << "new i " << c << std::endl;
		card = c;
		if (c == N)
		{
			add = glm::vec3(0, 0, -20);
			rot = glm::vec3(0, 0, 0);
		}
		else if (c == E)
		{
			add = glm::vec3(-20, 0, 0);
			rot = glm::vec3(0, M_PI / 2.0, 0);
		}
		else if (c == S)
		{
			add = glm::vec3(0, 0, 20);
			rot = glm::vec3(0, M_PI, 0);
		}
		else if (c == O)
		{
			add = glm::vec3(20, 0, 0);
			rot = glm::vec3(0, -M_PI / 2.0, 0);
		}
	}

	~BasicDir()
	{

	}
	
};


class	Chunk
{
	public: 
	
	GameObject					*render;
	GameObject					*collider;
	std::vector<std::string>	name_chunk = {"chunk0", "chunk1", "chunk2"};
	std::vector<std::string>	big_obs = {"Obstacle1"};

	Chunk(glm::vec3 vec)
	{
		collider = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Floor"));
		collider->GetComponent<Transform>()->SetPosition(vec + glm::vec3(0, -3.01, 0));
		render = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab(
			name_chunk[rand() % name_chunk.size()]
			));
		render->GetComponent<Transform>()->SetPosition(vec);
	}

	Chunk(glm::vec3 vec, std::string prefab)
	{
		collider = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Floor"));
		collider->GetComponent<Transform>()->SetPosition(vec + glm::vec3(0, -3.01, 0));
		render = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab(prefab));
		render->GetComponent<Transform>()->SetPosition(vec);
	}

	std::vector<GameObject	*> obstacle;

	void SetConf(glm::vec3 vec, glm::vec3 rot, bool corner)
	{
		Transform	*tr_render = render->GetComponent<Transform>();
		Transform	*tr_collider = collider->GetComponent<Transform>();
		tr_render->SetPosition(vec);
		tr_collider->SetPosition(vec + glm::vec3(0, -3.01, 0));
		tr_render->SetRotation(rot);

		if (corner)
			return ;

		int random_nb = rand() % 2;
		GameObject *tmp_obs;

		for (GameObject *obs : obstacle)
		{
			obs->SetDestroy(true);
		}
		obstacle = std::vector<GameObject	*>();
		if (random_nb == 1)
		{
			std::vector<glm::vec3> rand_pos = { tr_render->Left() * 2.0f, glm::vec3(0, 0, 0), tr_render->Left() * -2.0f};
			std::random_shuffle ( rand_pos.begin(), rand_pos.end() );

			tmp_obs = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab(
				big_obs[rand() % big_obs.size()]
				));
			tmp_obs->GetComponent<Transform>()->SetPosition(vec + rand_pos[0]);
			float rand_rot = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2 * M_PI));
			tmp_obs->GetComponent<Transform>()->SetRotation(glm::vec3(0, rand_rot, 0));
			obstacle.push_back(tmp_obs);

		}
		else if (random_nb == 0)
		{
			std::vector<glm::vec3> rand_pos = { tr_render->Left() * 2.0f, glm::vec3(0, 0, 0), tr_render->Left() * -2.0f};
			std::random_shuffle ( rand_pos.begin(), rand_pos.end() );
			int random_count = rand() % 3;
			for (int i = 0; i < random_count; ++i)
			{
				tmp_obs = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("ObstacleCollider"));
				tmp_obs->GetComponent<Transform>()->SetPosition(vec + rand_pos[i]);
				obstacle.push_back(tmp_obs);
			}

		}
	}

	void print_tmp_cr(std::string name, glm::vec3 vec)
	{
		std::cout  << name << " (" << vec.x << "," << vec .y << "," << vec .z << ")" << std::endl;
	}

	bool	BelongTo(glm::vec3 pos)
	{
		glm::vec3	c_pos = collider->GetComponent<Transform>()->GetPosition();
		
/*		std::cout << "BelongTo" << std::endl ;
		print_tmp_cr("player", pos);
		print_tmp_cr("tile", c_pos);*/

		if (pos.x < c_pos.x - 10 || pos.x > c_pos.x + 10 ||
			pos.z < c_pos.z - 10 || pos.z > c_pos.z + 10)
			return (false);
		return (true);
	}

	~Chunk(){};

};

class ScriptChunkSpawner : public Script
{
	public:

	int	maxsize = 6;
	int	minsize = 4;
	BasicDir	cur_dir = BasicDir(N);

	Chunk*	last_turn = nullptr;
	Chunk*	next_proc = nullptr;
	Chunk*	cur_turn = nullptr;
	

	std::vector<Chunk *>	chunks_1;
	std::vector<Chunk *>	chunks_2;

	int	maxturn = 3;
	int left_i = 0;
	int right_i = 0;
	std::vector<Chunk *>	chunks_lefts;
	std::vector<Chunk *>	chunks_rights;

	bool					enculade = false;

	ScriptChunkSpawner() : Script("ScriptChunkSpawner") {}
	Script* Clone() { return new ScriptChunkSpawner(*this); }

	int				chunk_size = 10;

	Chunk			*PickTurnChunk(int &add_dir)
	{
		int random_nb = rand() % 2;
		Chunk			*ret = nullptr;

		if (random_nb)
		{
			ret = chunks_rights[right_i];
			right_i ++;
			if (right_i >= maxturn)
				right_i = 0;
			add_dir = 1;
		}
		else
		{
			ret = chunks_lefts[left_i];
			left_i ++;
			if (left_i >= maxturn)
				left_i = 0;
			add_dir = -1;
		}
		return ret;
	}

	void			RemoveUselessTurn()
	{
		int i = 0;
		for (Chunk *curanal : chunks_lefts)
		{
			if (curanal != cur_turn && curanal != next_proc && curanal != last_turn)
			{
				i++;
				curanal->SetConf(glm::vec3(0, -20, 0), glm::vec3(), true);
			}
		}
		for (Chunk *curanal : chunks_rights)
		{
			if (curanal != cur_turn && curanal != next_proc && curanal != last_turn)
			{
				i++;
				curanal->SetConf(glm::vec3(0, -20, 0), glm::vec3(), true);
			}
		}
		std::cout  << "wasting chunk " << i << std::endl; 
	}

	void			GenerateNext()
	{
		std::vector<Chunk *> *cur_chunks = nullptr;

		if (!enculade)
			cur_chunks = &chunks_1;
		else
			cur_chunks = &chunks_2;
		enculade = !enculade;

		std::vector<Chunk *> rep;
		Chunk	*before = last_turn;
		Chunk	*anal = nullptr;
		unsigned int	random_nb = minsize + rand() % (maxsize - minsize);

		std::random_shuffle ( (*cur_chunks).begin(), (*cur_chunks).end() );
		for (unsigned int i = 0; i < (*cur_chunks).size(); ++i)
		{
			rep.push_back((*cur_chunks)[i]);
			anal = (*cur_chunks)[i];
			if (i < random_nb)
			{
				anal->SetConf(before->render->GetComponent<Transform>()->GetPosition() + cur_dir.add, cur_dir.rot, false);
				before = anal;
			}
			else
				anal->SetConf(glm::vec3(0, -20, 0), glm::vec3(), false);
		}
		(*cur_chunks) = rep;

		int	add_dir;
		cur_turn = next_proc;
		next_proc = last_turn;
		last_turn = PickTurnChunk(add_dir);
		last_turn->SetConf(before->render->GetComponent<Transform>()->GetPosition() + cur_dir.add, cur_dir.rot, true);

		cur_dir = BasicDir(BasicDir::AddCard(cur_dir.card, add_dir));
	}


	void			Awake()
	{
		for (int i = 0; i < maxsize; ++i)
		{
			chunks_1.push_back(new Chunk(glm::vec3(0, 0, 20)));
			chunks_2.push_back(new Chunk(glm::vec3(0, 0, 20)));
		}
		for (int i = 0; i < maxturn; ++i)
		{
			chunks_rights.push_back(new Chunk(glm::vec3(0, 0, 30), "chunk_right")); 
			chunks_lefts.push_back(new Chunk(glm::vec3(0, 0, 30), "chunk_left")); 
		}
		last_turn = chunks_lefts[0];
		GenerateNext();
		GenerateNext();
		std::cout << "after assign " << cur_dir.card << std::endl;
	}

	void	CheckPos()
	{
		static GameObject	*player = Application::singleton->GetCurrentScene()->FindGameObject("Player");
		glm::vec3 pos = player->GetComponent<Transform>()->GetPosition();
		if (next_proc->BelongTo(pos))
		{
			ScriptControlPlayer	*ctrl = dynamic_cast<ScriptControlPlayer *>(player->GetComponent<Script>());
			bool 	have_to_turn = true;

			if (std::find(chunks_lefts.begin(), chunks_lefts.end(), next_proc) != chunks_lefts.end())
				have_to_turn = false;
			ctrl->IsInTurnPoint(next_proc->render->GetComponent<Transform>()->GetPosition(), have_to_turn);

			static int ite = 0;
			ite ++;
			std::cout << "belong " << ite << std::endl;
			GenerateNext();
			RemoveUselessTurn();
			std::cout << "end belong" << std::endl;
			//ScriptControlPlayer::instance = nullptr;
		}
	}

	void	Update()
	{
		CheckPos();
	}
};
