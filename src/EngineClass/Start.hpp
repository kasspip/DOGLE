#ifndef START_HPP
# define START_HPP

# include "DOGLE.hpp"
#include "IState.hpp"

	class Start : public IState
	{
		public:

			Start(void);
			Start(Start const &src);
			~Start(void);

			Start &operator=(Start const &rhs);
			
			void		RunState(Application & app, e_state	& currentState);
			std::string toString(void) const;

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, Start const &rhs);

#endif
