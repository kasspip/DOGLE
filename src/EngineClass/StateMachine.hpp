#ifndef STATEMACHINE_HPP
# define STATEMACHINE_HPP

# include "DOGLE.hpp"
# include "Application.hpp"
# include "Start.hpp"
#include "IState.hpp"

	class StateMachine
	{

		public:
			StateMachine(void);
			~StateMachine(void);
			StateMachine &operator=(StateMachine const &rhs);
			std::string toString(void) const;
			void		RunApplication(Application & app);

		private:
			StateMachine(StateMachine const &src);
			Application		*_app;
			e_state			_currentState;
			static IState	*_states[];
	};

	std::ostream	&operator<<(std::ostream &o, StateMachine const &rhs);

#endif
