#include "Camera.hpp"
#include "GameObject.hpp"
#include "Engine.hpp"

Camera	*Camera::_main = nullptr;


// CONSTRUCTOR DESTRUCTOR //

Camera::Camera(float FOV, float clipN, float clipF)
{
	std::cout << "Construct camera" << std::endl;
	type = "Camera";
	fov = FOV;
	clipNear = clipN;
	clipFar = clipF;

	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(Camera const &src)
{
	std::cout << "Construct camera" << std::endl;
	type = "Camera";
	*this = src;
}

Camera::~Camera(void)
{
	std::cout << "Destruct camera" << std::endl;
}

// OVERLOADS //

Camera& 		Camera::operator=(Camera const &rhs)
{
	fov = rhs.fov;
	clipNear = rhs.clipNear;
	clipFar = rhs.clipFar;
	cameraFront = rhs.cameraFront;
	cameraUp = rhs.cameraUp;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Camera const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

glm::mat4		Camera::Projection(int winW, int winH)
{
	return glm::perspective(fov, (GLfloat)winW / (GLfloat)winH, clipNear, clipFar);
}

glm::mat4		Camera::View()
{

	glm::vec3 front;
	glm::vec3 rot = transform->GetRotation();
	glm::vec3 pos = transform->GetPosition();

	front.x = cos(rot.x) * sin(rot.y);
	front.y = sin(rot.x);
	front.z = (cos(rot.x) * cos(rot.y)) * -1;

	cameraFront = glm::normalize(front);

	return glm::lookAt(	pos, 
						pos + cameraFront,
						cameraUp);
}

std::string		Camera::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Camera #" << std::endl;
	ss << "FOV : " << fov << std::endl;
	ss << "Near clipping : " << clipNear << std::endl;
	ss << "Far clipping : " << clipFar << std::endl;
	return ss.str();
}

void			Camera::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
		TABS = "\t\t\t";

	file << TABS << "CAMERA:" 
	<< fov << SEPARATOR
	<< clipNear << SEPARATOR
	<< clipFar << std::endl;
}



// PRIVATE //

// GETTER SETTER //
GameObject*		Camera::GetMainCamera() { return _main->gameObject; }

void			Camera::SetMainCamera(GameObject* go)  
{ 
	Camera* camera = go->GetComponent<Camera>();
	if (camera == nullptr)
		throw DError() << msg("Camera.SetMainCamera(). No camera component found in " + go->name);
	_main = camera; 
}