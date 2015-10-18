#ifndef START_HPP
# define START_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Start : public IState
	{
		public:

			Start(void);
			~Start(void);

			
			void		RunState(Application & app, e_state	& currentState);
			std::string toString(void) const;

		private:
			
			Start(Start const &src);
			Start &operator=(Start const &rhs);
	
	};

	std::ostream	&operator<<(std::ostream &o, Start const &rhs);

#endif
