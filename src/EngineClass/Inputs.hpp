#ifndef INPUTS_HPP
# define INPUTS_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Inputs : public IState
	{
		public:

			Inputs(void);
			~Inputs(void);
			
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);
			bool		KeyPressed(int key);
			bool		KeyReleased(int key);
			bool		KeyDown(int key);

			
			static void			KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void			KeyState(GLFWwindow *window, int id);
			static Inputs		*singleton;
			static int			_key[];

		private:

			Inputs &operator=(Inputs const &rhs);
			Inputs(Inputs const &src);
			
	};

	std::ostream	&operator<<(std::ostream &o, Inputs const &rhs);
#endif
