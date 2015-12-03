#ifndef LIGHT_HPP
# define LIGHT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
# include <assimp/cimport.h>


	class Light : public IComponent
	{
		public:

			Light(float intensity, glm::vec3 col = glm::vec3(1,1,1));
			Light(Light const &src);
			~Light(void);
		
			Light &operator=(Light const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);

			float		intensity;
			glm::vec3 	color;

		private:
			Light(void);
	
	};

	std::ostream	&operator<<(std::ostream &o, Light const &rhs);

#endif
