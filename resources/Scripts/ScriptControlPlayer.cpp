#include "DOGLE.hpp"
#include "Script.hpp"

enum e_dash_pos
{
	LEFT = -1,
	MID,
	RIGHT
};

class ScriptControlPlayer : public Script
{
	public:

		GameObject* 	child = nullptr;
		float 			baseSpeed = 3;
		e_dash_pos		dash_pos = MID;
		float			move_speed = 10;
		bool			mooving = false;
		GameObject*		floor = nullptr;

		static ScriptControlPlayer	*instance;

		ScriptControlPlayer() : Script("ScriptControlPlayer") {}
		Script* 		Clone() { return new ScriptControlPlayer(*this); }

		void			Awake()
		{
			GameObject	*cam = Camera::GetMainCamera();
			floor = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("Floor"));
			std::cout << floor->GetComponent<Collider>()->mass << std::endl;
			glm::vec3	cam_pos = cam->GetComponent<Transform>()->GetPosition();
			glm::vec3	my_pos = transform->GetPosition();
			pad = cam_pos - my_pos;

		}

		void			Update()
		{
			(void)floor;
			if (Inputs::singleton->KeyDown(GLFW_KEY_W))
			{
				std::cout << "key press W (MoveForward)" << std::endl;
				MoveForward();
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_A))
			{
				std::cout << "key press A (turn left)" << std::endl;
				Turn(true);
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_D))
			{
				std::cout << "key press D (turn right)" << std::endl;
				Turn(false);
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_SPACE))
			{
				std::cout << "key press espace (jump)" << std::endl;
				Jump();
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_C))
			{
				std::cout << "key press C (dash left)" << std::endl;
				Dash(true);
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_V))
			{
				std::cout << "key press V (dash right)" << std::endl;
				Dash(false);
			}
			UpdateDash();
			UpdateTurn();
			UpdateMoveForward();
			UpdateCameraPos();
			UpdateJump();
		}

		void	OnCollisionEnter(GameObject *go)
		{
			if (go->name == "Floor")
			{
				if (jumping)
				{
					if (mid_jump)
						jumping = false;
					else
						start_jump = true;
				}
			}
		}


	private:

		void			UpdateCameraPos()
		{
			GameObject	*cam = Camera::GetMainCamera();
			Transform	*cam_tr = cam->GetComponent<Transform>();
			glm::vec3	cam_pos = cam->GetComponent<Transform>()->GetPosition();
			glm::vec3	my_pos = transform->GetPosition();
			
			cam_pos = my_pos +  transform->Forward() * -pad.z + glm::vec3(0, 3, 0);
			cam_pos.y = cam_tr->_position.y;
			cam_pos -= cam_pad;
			cam_tr->SetPosition(cam_pos);
			cam_tr->SetRotation(transform->_rotation.x, -transform->_rotation.y + M_PI, cam_tr->_rotation.z);
		}

		glm::vec3		dash_target;
		bool			dashing = false;
		float			dash_speed = 0.1;
		float			dash_timer = 0;
		glm::vec3		pad;
		float			mul_dash = 1;

		glm::vec3		cam_pad;

		void			UpdateDash()
		{
			if (dashing)
			{
				float delta = Engine::singleton->deltaTime;
				if (dash_timer + delta > dash_speed)
				{
					delta = dash_speed - dash_timer;
					dashing = false;
					//std::cout << cam_pad << std::endl;
				}
				glm::vec3 inc = dash_target * (float)(delta / dash_speed);
				cam_pad += inc;
				transform->SetPosition(transform->GetPosition() + inc);
				dash_timer += delta;
			}
		}

		void			Dash(bool b)
		{
			if (dashing || turning)
				return ;
			float mul = mul_dash;
			if (b)
			{		
				if (dash_pos == LEFT)
					return ;
				std::cout << "Dash LEFT" << std::endl;
				dash_pos = static_cast<e_dash_pos>(dash_pos - 1);			
			}
			else
			{
				if (dash_pos == RIGHT)
					return ;
				std::cout << "Dash RIGHT" << std::endl;
				mul *= -1;
				dash_pos = static_cast<e_dash_pos>(dash_pos + 1);			
			}
			std::cout << "! dash_pos = " << dash_pos << std::endl;
			dashing = true;
			dash_target = transform->Left() * mul_dash * mul;
			dash_timer = 0;
		}

		float			turn_speed = 0.5;
		float			turn_timer = 0;
		float			turn_target;
		bool			turning = false;

		void			UpdateTurn()
		{
			glm::vec3	my_rot = transform->GetRotation();

			if (turning)
			{
				float delta = Engine::singleton->deltaTime;
				if (turn_timer + delta > turn_speed)
				{
					delta = turn_speed - turn_timer;
					turning = false;
					mooving = true;
					std::cout << "turnover" << std::endl;
				}
				my_rot.y += turn_target * (float)(delta / turn_speed);
				transform->SetRotation(my_rot);

				turn_timer += delta;

			}
		}

		void			Turn(bool b)
		{
			if (turning || dashing)
				return ;
			cam_pad = glm::vec3();
			dash_pos = MID;
			mooving = false;
			turning = true;
			turn_timer = 0;
			if (b)
				std::cout << "Turn Left" << std::endl;
			else
				std::cout << "Turn Right" << std::endl;
			float mul = M_PI / 2;
			if (!b)
				mul *= -1;
			turn_target = mul;
		}

		void		UpdateMoveForward()
		{
			if (!mooving)
				return ;
			gameObject->GetComponent<Collider>()->force = transform->Forward() * move_speed;

		}

		void		MoveForward()
		{
			mooving = true;
			std::cout << "MoveForward" << std::endl;
		}

		glm::vec3		jumpower = glm::vec3(0, 5, 0);
		bool			jumping = false;
		bool			start_jump = false;
		bool			mid_jump = false;

		void			UpdateJump()
		{
			if (jumping)
			{
				if (start_jump)
					start_jump = false;
				else
					mid_jump = true;
			}
		}

		void		Jump()
		{
			if (jumping)
				return ;
			std::cout << "Jump" << std::endl;
			jumping = false;
			start_jump = false;
			mid_jump = false;
			gameObject->GetComponent<Collider>()->impulse = jumpower;
		}



};
