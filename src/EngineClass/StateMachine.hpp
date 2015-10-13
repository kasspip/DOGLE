#ifndef STATEMACHINE_HPP
# define STATEMACHINE_HPP

# include "DOGLE.hpp"
# include "Application.hpp"
# include "IState.hpp"
# include "Start.hpp"
# include "Physics.hpp"
# include "Inputs.hpp"
# include "GameLogic.hpp"
# include "Render.hpp"
# include "GUI.hpp"
# include "Pause.hpp"
# include "Destroy.hpp"
# include "Stop.hpp"

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
