#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Physics : public IState
	{
		public:

			Physics(void);
			~Physics(void);
		
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

		private:

			Physics &operator=(Physics const &rhs);
			Physics(Physics const &src);
	};

	std::ostream	&operator<<(std::ostream &o, Physics const &rhs);

#endif
