#ifndef SCRIPT_HPP
# define SCRIPT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
# include "Inputs.hpp"


	class Script : public IComponent
	{
		public:
			Script(std::string n);
			Script(Script const &src);
			virtual ~Script(void);
			Script &operator=(Script const &rhs);

			virtual void			Update();
			virtual void			Awake();
			virtual void			OnDestroy();

			
			virtual void			Save(std::ofstream &file);
			virtual std::string 	toString(void) const;

			void					Destroy(GameObject *go);

			std::string name;

		private:
	};

#endif
