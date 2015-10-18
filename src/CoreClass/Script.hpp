#ifndef SCRIPT_HPP
# define SCRIPT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
//# include "Engine.hpp"
# include "Inputs.hpp"


	class Script : public IComponent
	{
		public:
			Script(std::string n);
			Script(Script const &src);
			virtual ~Script(void);
			Script &operator=(Script const &rhs);

			virtual void			Update();

			
			virtual void			Save(std::ofstream &file);
			virtual std::string 	toString(void) const;

			std::string name;

		private:
	};

#endif
