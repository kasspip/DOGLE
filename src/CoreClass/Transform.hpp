#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"


	class Transform : public IComponent
	{
		static size_t	counter;

		public:
			Transform();
			Transform(glm::vec3 pos, glm::vec3 rot = glm::vec3(0.0f), glm::vec3 sc = glm::vec3(1.0f));
			Transform(Transform const &src);
			~Transform(void);
		
			Transform &operator=(Transform const &rhs);
			
			glm::vec3	position;
			glm::vec3	rotation;
			glm::vec3	scale;
			Transform	*parent;

			void		CalculateTransform();
			std::string toString(void) const;
			void		Save(std::ofstream &file);
			glm::mat4	GetMatrice();

		private:

			glm::mat4	_transform;
			glm::mat4	_local;
			glm::mat4	_world;
	};

	std::ostream	&operator<<(std::ostream &o, Transform const &rhs);

#endif
