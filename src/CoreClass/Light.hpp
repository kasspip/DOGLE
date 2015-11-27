#ifndef LIGHT_HPP
# define LIGHT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
# include <assimp/cimport.h>


	class Light : public IComponent
	{
		public:

			Light(void);
			Light(Light const &src);
			~Light(void);
		
			Light &operator=(Light const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);


			aiColor4D 	color;

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, Light const &rhs);

#endif
