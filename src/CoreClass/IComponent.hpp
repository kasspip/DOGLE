#ifndef ICOMPONENT_HPP
# define ICOMPONENT_HPP

# include "DOGLE.hpp"

	class IComponent
	{
		public:

			virtual ~IComponent(void){};

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, IComponent const &rhs);

#endif
