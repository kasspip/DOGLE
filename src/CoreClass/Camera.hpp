#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
class Transform;

	class Camera : public IComponent
	{
		public:
			Camera(void);
			Camera(float FOV, float clipN, float clipF);
			Camera(Camera const &src);
			~Camera(void);
			
			Camera 		&operator=(Camera const &rhs);


			std::string toString(void) const;
			void		Save(std::ofstream &file);
			glm::mat4	GetProjection(int winW, int winH);

		private:

			float		_fov;
			float		_clipNear;
			float		_clipFar;
	};

	std::ostream	&operator<<(std::ostream &o, Camera const &rhs);

#endif
