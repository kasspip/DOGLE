#ifndef ISTATE_HPP
# define ISTATE_HPP

# include "DOGLE.hpp"
# include "Scene.hpp"

class Application;

	class IState
	{
		public:
			virtual ~IState(void){};
			virtual void	RunState(Application & app, e_state	& currentState) = 0;

		private:
	};

#endif
