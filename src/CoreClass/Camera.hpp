#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
class Transform;

	class Camera : public IComponent
	{
		public:
			Camera(float FOV = 45.0f, float clipN = 0.1f, float clipF = 100.0f);
			Camera(Camera const &src);
			~Camera(void);
			
			Camera 		&operator=(Camera const &rhs);


			std::string toString(void) const;
			void		Save(std::ofstream &file);
			glm::mat4	GetProjection(int winW, int winH);

			static GameObject*	GetMainCamera();
			static void			SetMainCamera(GameObject* go);

		private:
			
			static Camera		*_main;
		
			float		_fov;
			float		_clipNear;
			float		_clipFar;
	};

	std::ostream	&operator<<(std::ostream &o, Camera const &rhs);

#endif
