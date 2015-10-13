#ifndef GAMELOGIC_HPP
# define GAMELOGIC_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class GameLogic : public IState
	{
		public:

			GameLogic(void);
			~GameLogic(void);
			
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

		private:

			GameLogic &operator=(GameLogic const &rhs);
			GameLogic(GameLogic const &src);
	};

	std::ostream	&operator<<(std::ostream &o, GameLogic const &rhs);

#endif
