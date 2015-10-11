#ifndef ISTATE_HPP
# define ISTATE_HPP

# include "DOGLE.hpp"
# include "Application.hpp"
# include "Scene.hpp" 
# include "GameObject.hpp"
# include "Skin.hpp"
class Application;


	class IState
	{
		public:
			virtual ~IState(void){};
			virtual void	RunState(Application & app, e_state	& currentState) = 0;
		private:
	};

#endif
