#ifndef PAUSE_HPP
# define PAUSE_HPP

# include "DOGLE.hpp"
# include "IState.hpp"
# include "Engine.hpp"

	class Pause : public IState, public Engine
	{
		public:

			Pause(void);
			~Pause(void);

			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);


		private:

			Pause(Pause const &src);
			Pause &operator=(Pause const &rhs);
	};

	std::ostream	&operator<<(std::ostream &o, Pause const &rhs);

#endif
