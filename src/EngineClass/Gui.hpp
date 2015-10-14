#ifndef GUI_HPP
# define GUI_HPP

# include "DOGLE.hpp"
# include "IState.hpp"
# include "Engine.hpp"

	class Gui : public IState, public Engine
	{
		public:

			Gui(void);
			~Gui(void);
	
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

		private:

			Gui &operator=(Gui const &rhs);
			Gui(Gui const &src);
	
	};

	std::ostream	&operator<<(std::ostream &o, Gui const &rhs);

#endif
