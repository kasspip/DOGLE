#ifndef SCRIPT_HPP
# define SCRIPT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
# include "Inputs.hpp"
# include "Engine.hpp"

	class Script : public IComponent
	{
		public:
			Script(std::string n);
			Script(Script const &src);
			virtual ~Script(void);
			Script &operator=(Script const &rhs);

			virtual Script* 		Clone() = 0; 

			virtual void			Update();
			virtual void			Awake();
			virtual void			OnGUI();
			virtual void			OnPause();
			virtual void			OnDestroy();
			virtual void			OnStop();
			virtual void			OnCollisionEnter(int i);
			
			virtual void			Save(std::ofstream &file);
			virtual std::string 	toString(void) const;

			void					Destroy(GameObject *go);

			std::string name;

		private:
	};

#endif
