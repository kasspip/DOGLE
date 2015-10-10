#ifndef SKIN_HPP
# define SKIN_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

	class Skin : public IComponent
	{
		public:

			Skin(void);
			Skin(Skin const &src);
			~Skin(void);
		
			Skin &operator=(Skin const &rhs);
			
			std::string toString(void) const;

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, Skin const &rhs);

#endif
