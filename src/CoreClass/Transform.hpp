#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

class GameObject;

	class Transform : public IComponent
	{
		public:
			Transform(GameObject * owner);
			Transform(Transform const &src, GameObject* owner);
			~Transform(void);
		
			Transform &operator=(Transform const &rhs);
			
			glm::vec3	position;
			glm::vec3	rotation;
			glm::vec3	scale;
			Transform	*parent;

			void		CalculateTransform();
			std::string toString(void) const;
			void		Save(std::ofstream &file);
			GameObject*	GetOwner();
			glm::mat4	GetTransform();
		private:
			Transform(void);

			GameObject	*_owner;
			glm::mat4	_transform;
			glm::mat4	_local;
			glm::mat4	_world;
	};

	std::ostream	&operator<<(std::ostream &o, Transform const &rhs);

#endif
