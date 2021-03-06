#ifndef COLLIDER_HPP
# define COLLIDER_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
# include "Skin.hpp"
# include "Transform.hpp"

	class Collider : public IComponent
	{
		public:

			Collider(glm::vec3 pos, glm::vec3 sz, bool b = true, float massf = 1);
			Collider(GameObject *go, bool b = true, float massf = 1);
			Collider(glm::vec3 pos, glm::vec3 sz, bool b, float massf, GameObject *go);
			~Collider(void);
		
			Collider &operator=(Collider const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);

			glm::vec3	center;
			glm::vec3	size;
			bool		enable;
			bool		isPhy;
			float		mass;

			glm::vec3 	impulse;
			glm::vec3 	force;

			void		*physic_ptr;


			void		ForgivePhysicRotation();

			bool		IsSkinned();
		private:
			Collider(void);
			Collider(Collider const &src);
			const bool	_skinned;
	
	};

	std::ostream	&operator<<(std::ostream &o, Collider const &rhs);

#endif
