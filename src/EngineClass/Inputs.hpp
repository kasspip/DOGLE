#ifndef INPUTS_HPP
# define INPUTS_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Inputs : public IState
	{
		static bool		_key[];
		static void		KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static bool		EventPressed(int key_name, int key, int action);

		public:

			Inputs(void);
			~Inputs(void);
			
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);
			bool		KeyIsPressed(e_key key);

		private:

			Inputs &operator=(Inputs const &rhs);
			Inputs(Inputs const &src);
			
	};

	std::ostream	&operator<<(std::ostream &o, Inputs const &rhs);

#endif
