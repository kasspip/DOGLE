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
			


			glm::mat4	CalculateTransform();
			std::string toString(void) const;
			void		Save(std::ofstream &file);
			glm::mat4	GetMatrice();
			
			glm::vec3	GetPosition() const;
			glm::vec3	GetRotation() const;
			glm::vec3	GetScale() const;
			glm::vec3	Forward() const;
			glm::vec3	Up() const;
			glm::vec3	Left() const;

			glm::vec3	_position;
			glm::vec3	_rotation;
			glm::vec3	_scale;

			void		SetPosition(float x, float y, float z);
			void		SetRotation(float x, float y, float z);
			void		SetScale(float x, float y, float z);
			void		SetPosition(glm::vec3 v);
			void		SetRotation(glm::vec3 v);
			void		SetScale(glm::vec3 v);

		private:

			glm::mat4	_local;
			glm::mat4	_world;

			void		_SetPhysicPosition();
			void		_SetPhysicRotation();
			void		_SetPhysicScale();
			void		_SetModuloRotation();
	};

	std::ostream	&operator<<(std::ostream &o, Transform const &rhs);

#endif
