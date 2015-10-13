#ifndef STOP_HPP
# define STOP_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Stop : public IState
	{
		public:

			Stop(void);
			~Stop(void);
					
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

		private:
			Stop(Stop const &src);
			Stop &operator=(Stop const &rhs);
	};

	std::ostream	&operator<<(std::ostream &o, Stop const &rhs);

#endif
