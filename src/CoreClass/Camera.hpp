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

			static GameObject*	GetMainCamera();
			static void			SetMainCamera(GameObject* go);

			glm::mat4			Projection(int winW, int winH);
			glm::mat4			View();

			std::string 		toString(void) const;
			void				Save(std::ofstream &file);

			float		fov;
			float		clipNear;
			float		clipFar;

			glm::vec3	cameraFront;
			glm::vec3	cameraUp;

		private:
			
			static Camera		*_main;

	};

	std::ostream	&operator<<(std::ostream &o, Camera const &rhs);

#endif
