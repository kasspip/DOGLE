#ifndef INPUTS_HPP
# define INPUTS_HPP

# include "DOGLE.hpp"
# include "IState.hpp"
# include "Engine.hpp"

	class Inputs : public IState, public Engine
	{
		public:

			Inputs(void);
			~Inputs(void);
			
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

		private:

			Inputs &operator=(Inputs const &rhs);
			Inputs(Inputs const &src);
			
			static void			_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static key_event	_SetEvent(int key_name, int key, int action);
	};

	std::ostream	&operator<<(std::ostream &o, Inputs const &rhs);

#endif
