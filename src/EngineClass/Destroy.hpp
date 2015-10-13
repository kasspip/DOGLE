#ifndef DESTROY_HPP
# define DESTROY_HPP

# include "DOGLE.hpp"
# include "IState.hpp"

	class Destroy : public IState
	{
		public:

			Destroy(void);
			~Destroy(void);

			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);

		private:
			Destroy(Destroy const &src);
			Destroy &operator=(Destroy const &rhs);
	};

	std::ostream	&operator<<(std::ostream &o, Destroy const &rhs);

#endif
