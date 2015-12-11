#include "DOGLE.hpp"
#include "Script.hpp"

#ifndef SCRIPTCONTROLPLAYER	
#define SCRIPTCONTROLPLAYER

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
		Transform* 		light = nullptr;
		e_dash_pos		dash_pos = MID;
		e_dash_pos		turn_pos = MID;
		float			move_speed = 10;
		bool			mooving = false;

		glm::vec3 		prevPosition;
		double 			totalDistance;
		bool			isDead;
		int				score;

		static ScriptControlPlayer	*instance;

		ScriptControlPlayer() : Script("ScriptControlPlayer") {}
		Script* 		Clone() { return new ScriptControlPlayer(*this); }

		void print_tmp_cr(std::string name, glm::vec3 vec)
		{
			std::cout  << name << " (" << vec.x << "," << vec .y << "," << vec .z << ")" << std::endl;
		}

		void			Awake()
		{
			GameObject	*cam = Camera::GetMainCamera();
			glm::vec3	cam_pos = cam->GetComponent<Transform>()->GetPosition();
			glm::vec3	my_pos = transform->GetPosition();
			pad = cam_pos - my_pos;
			light =  Application::singleton->GetCurrentScene()->FindGameObject("Light")->GetComponent<Transform>();
			transform->SetRotation(0, M_PI, 0);
			
			prevPosition = transform->_position;
			totalDistance = 0;
			isDead = false;
		}

		void			Update()
		{
			if (isDead)
			{
				Die();
				return;
			}

			if (Inputs::singleton->KeyDown(GLFW_KEY_W))
			{
				static bool started = false;
				if (!started)
				{
					started = true;
					std::cout << "key press W (MoveForward)" << std::endl;
					MoveForward(true);
				}
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_ESCAPE))
			{
				Application::singleton->Stop();
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_A))
			{
				std::cout << "key press A (turn left)" << std::endl;
				if (can_turn)
					turn_pos = LEFT;
				else
					Dash(true);
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_D))
			{
				std::cout << "key press D (turn right)" << std::endl;
				if (can_turn)
					turn_pos = RIGHT;
				else
					Dash(false);
				//Turn false
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_SPACE))
			{
				std::cout << "key press espace (jump)" << std::endl;
				Jump();
			}
			
			if (Inputs::singleton->KeyDown(GLFW_KEY_E))
			{
				std::cout << "Rotation y" << transform->_rotation.y << std::endl;
				std::cout << "Vector Forward " << transform->_rotation.y << std::endl;
			}

			/*if (Inputs::singleton->KeyDown(GLFW_KEY_C))
			{
				std::cout << "key press C (dash left)" << std::endl;
				turn_pos = 
				Dash(true);
			}
			if (Inputs::singleton->KeyDown(GLFW_KEY_V))
			{
				std::cout << "key press V (dash right)" << std::endl;
				Dash(false);
			}*/
			UpdateDash();
			UpdateTurn();
			UpdateCanTurn();
			UpdateCameraPos();
			UpdateLightPos();
			UpdateJump();
			UpdateText();

		}

		void	OnCollisionEnter(GameObject *go)
		{
			if (!isDead && go->name.find("Bonus") != std::string::npos)
			{
				AddScore(10);
				Destroy(go);
			}
			else if ( !isDead && go->name.find("Floor") == std::string::npos)
			{
				std::cout << "take down ! : " << go->name << std::endl;
				isDead = true;
				std::cout << "bolo" << std::endl;
			}
		}

		void		AddScore(int val)
		{
			score += val;

			Text *textScore =  Application::singleton->GetCurrentScene()->FindGameObject("TextScore")->GetComponent<Text>();

			std::stringstream ss;
			ss << "Score : " << score;
			textScore->text = ss.str();
		}

		void		Die()
		{	
			static bool set = false;

			if (!set)
			{
				mooving = false;
				gameObject->GetComponent<Collider>()->force = glm::vec3();
				set = true;
			}

			glm::vec3 newRot = glm::vec3 (transform->_rotation.x, transform->_rotation.y + 10 * Engine::singleton->deltaTime, transform->_rotation.z);
			transform->SetRotation( newRot );
		}

		void		UpdateText()
		{
			float newDistance = glm::distance(prevPosition, transform->_position);
			prevPosition = transform->_position;
			
			totalDistance += newDistance;

 			Text *text = gameObject->GetComponent<Text>();
 			std::stringstream ss;
 			ss << "Distance : " << static_cast<int>(totalDistance);
 			text->text = ss.str();
 		}


		bool		can_turn = false; 
		glm::vec3	can_turn_pos;
		bool		have_to_turn;

		void		IsInTurnPoint(glm::vec3 allower, bool bo)
		{
			have_to_turn = bo;
			if (dash_pos == LEFT)
				Dash(false);
			else if (dash_pos == RIGHT)
				Dash(true);
			can_turn_pos = allower;
			can_turn_pos.y = transform->_position.y;
			print_tmp_cr("TARGET TURN", can_turn_pos);
			print_tmp_cr("POS", transform->_position);
			turn_pos = MID;
			can_turn = true;
		}


	private:

		void			UpdateCanTurn()
		{
			if (!can_turn)
				return ;
			float dist = glm::distance(transform->_position, can_turn_pos);
		//	std::cout << "dist = " << dist << std::endl;
			if (dist < 0.2)
			{
				MoveForward(false);
				transform->SetPosition(can_turn_pos);
				std::cout << "TIME TO TURN" << std::endl;
				can_turn = false;
				if (turn_pos == RIGHT)
				{
					if (!have_to_turn)
					{
						std::cout << "OUBLI PAS DE TOURNER" << std::endl;
						isDead = true;
					}
					Turn(false);
				}
				else if (turn_pos == LEFT)
				{
					if (have_to_turn)
					{
						std::cout << "OUBLI PAS DE TOURNER" << std::endl;
						isDead = true;
					}
					Turn(true);

				}
				else
				{
					std::cout << "OUBLI PAS DE TOURNER" << std::endl;
					isDead = true;
				}
			}
		}


		void			UpdateLightPos()
		{
			light->SetPosition(transform->GetPosition() + glm::vec3(0, 3.5, 0));
		}

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
		float			mul_dash = 2;

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
				}
				glm::vec3 inc = dash_target * (float)(delta / dash_speed);
				cam_pad += inc;
				transform->SetPosition(transform->GetPosition() + inc);
				dash_timer += delta;
			}
		}

		void			Dash(bool b)
		{
			if (!can_turn && (dashing || turning))
				return ;
			float mul = 1;
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
			(void)(b);
/*			print_tmp_cr("LEFT", transform->Left());
			print_tmp_cr("CURPOS", transform->GetPosition());
			transform->SetPosition(transform->Left() + transform->GetPosition());
			print_tmp_cr("AFTER POS", transform->GetPosition());*/
		}

		float			turn_speed = 0.2;
		float			turn_timer = 0;
		float			turn_target;
		bool			turning = false;

		bool AreSame(double a, double b)
		{
    		return fabs(a - b) < 0.6;
		}

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
					std::cout << "turnover" << std::endl;
				print_tmp_cr("POS AFTER TURN", transform->_position);

				}
				my_rot.y += turn_target * (float)(delta / turn_speed);
				if (!turning)
				{
					my_rot.y = fmod(my_rot.y, M_PI * 2);
					if (AreSame(my_rot.y, 0))
						my_rot.y = 0;
					if (AreSame(my_rot.y, M_PI / 2))
						my_rot.y = M_PI / 2;
					if (AreSame(my_rot.y, M_PI))
						my_rot.y = M_PI;
					if (AreSame(my_rot.y, M_PI / 2 * 3))
						my_rot.y = M_PI / 2 * 3;
					if (AreSame(my_rot.y, M_PI * 2))
						my_rot.y = M_PI * 2;

					transform->SetRotation(my_rot);
					
					std::cout << "Rotation y" << transform->_rotation.y << std::endl;
					MoveForward(true);
				}
				else
					transform->SetRotation(my_rot);
				turn_timer += delta;

			}
		}

		void			Turn(bool b)
		{
			if (turning || dashing)
				return ;
			print_tmp_cr("POS BEFORE TURN", transform->_position);

			cam_pad = glm::vec3();
			dash_pos = MID;
			MoveForward(false);
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



		void		MoveForward(bool b)
		{
			mooving = b;
			Collider *collider = gameObject->GetComponent<Collider>();
			
			if (collider == nullptr)
				return ;

			if (mooving)
				collider->force = transform->Forward() * move_speed;
			else
				collider->force = glm::vec3();
			std::cout << "MoveForward " << b << std::endl;
		}

		float			jumpower = 1.7;
		float			jumptarget = 0;
		float			jumpstart = 0;
		bool			jumping = false;

		float			jump_timer = 0;
		float			jump_speed = 0.25;

		bool			mode_jump = false;
		bool			mode_jump_high = false;

		void			UpdateJump()
		{
			if (jumping)
			{
					float delta = Engine::singleton->deltaTime;
					if (jump_timer + delta > jump_speed)
					{
						delta = jump_speed - jump_timer;
						if (mode_jump)
						{
							mode_jump = false;
							mode_jump_high = true;
						}
						else if (mode_jump_high)
						{
							mode_jump_high = false;
							mode_jump = false;
						}
						else
							jumping = false;
						jump_timer = 0;
						std::cout << "JUMPover" << std::endl;
					}
					float addy = jumpower * (float)(delta / jump_speed);
					if (!mode_jump)
						addy *= -1;
					if (mode_jump_high)
						addy = 0;
					if (jumping)
						transform->SetPosition(transform->GetPosition() + glm::vec3(0, addy, 0));
					else
					{
						glm::vec3 tmpy = transform->GetPosition();
						tmpy.y = jumpstart;
						transform->SetPosition(tmpy);
					}
					jump_timer += delta;
			}
		}


		void		Jump()
		{
			if (jumping)
				return ;
			std::cout << "Jump" << std::endl;
			jumping = true;
			mode_jump = true;
			jump_timer = 0;
			jumpstart = transform->GetPosition().y;
			jumptarget = transform->GetPosition().y+ jumpower;
					
		}


};

#endif