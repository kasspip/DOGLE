#ifndef INITIALISATION_HPP
# define INITIALISATION_HPP

# include "DOGLE.hpp"
#include "IState.hpp"

	class Initialisation : public IState
	{
		public:

			Initialisation(void);
			Initialisation(Initialisation const &src);
			~Initialisation(void);
		
			Initialisation &operator=(Initialisation const &rhs);
			
			std::string toString(void) const;

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, Initialisation const &rhs);

#endif
