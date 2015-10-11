#ifndef STATEMACHINE_HPP
# define STATEMACHINE_HPP

# include "DOGLE.hpp"
# include "Application.hpp"
# include "IState.hpp"
# include "Initialisation.hpp"

	class StateMachine
	{
		typedef enum	e_state
		{
			INITIALISATION,
			STATE_NBR
		}				e_state;

		public:
			StateMachine(void);
			~StateMachine(void);
			StateMachine &operator=(StateMachine const &rhs);
			std::string toString(void) const;

		private:
			StateMachine(StateMachine const &src);
			Application		*_app;
			e_state			_currentState;
			static IState	*_states[];
	};

	std::ostream	&operator<<(std::ostream &o, StateMachine const &rhs);

#endif
