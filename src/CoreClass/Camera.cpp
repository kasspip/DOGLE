#include "Camera.hpp"
#include "GameObject.hpp"

Camera	*Camera::_main = NULL;


// CONSTRUCTOR DESTRUCTOR //

Camera::Camera(void)
{
	std::cout << "Construct camera" << std::endl;
	_fov = 45.0f;
	_clipNear = 0.1f;
	_clipFar = 100.0f;
}

Camera::Camera(float FOV, float clipN, float clipF)
{
	std::cout << "Construct camera" << std::endl;
	_fov = FOV;
	_clipNear = clipN;
	_clipFar = clipF;
}

Camera::Camera(Camera const &src)
{
	std::cout << "Construct camera" << std::endl;
	*this = src;
}


Camera::~Camera(void)
{
	std::cout << "Destruct camera" << std::endl;
}

// OVERLOADS //

Camera& 		Camera::operator=(Camera const &rhs)
{
	_fov = rhs._fov;
	_clipNear = rhs._clipNear;
	_clipFar = rhs._clipFar;
	return *this;
}


std::ostream	&operator<<(std::ostream & o, Camera const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

glm::mat4		Camera::GetProjection(int winW, int winH)
{
	return glm::perspective(_fov, (GLfloat)winW / (GLfloat)winH, _clipNear, _clipFar);
}

std::string		Camera::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Camera #" << std::endl;
	ss << "FOV : " << _fov << std::endl;
	ss << "Near clipping : " << _clipNear << std::endl;
	ss << "Far clipping : " << _clipFar << std::endl;
	return ss.str();
}

void			Camera::Save(std::ofstream &file)
{
	file << "\t\t\tCAMERA : " << std::endl;
	file << "\t\t\tFOV : " << _fov << std::endl;
	file << "\t\t\tCLIPN : " << _clipNear << std::endl;
	file << "\t\t\tCLIPF : " << _clipFar << std::endl;
}

// PRIVATE //

// GETTER SETTER //
GameObject*				Camera::GetMainCamera() { return _main->gameObject; }

void					Camera::SetMainCamera(GameObject* go)  
{ 
	Camera* camera = go->GetComponent<Camera>();
	if (camera == NULL)
		throw DError() << msg("Camera.SetMainCamera(). No camera component found in " + go->name);
	_main = camera; 
}