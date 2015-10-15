#include "Transform.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Transform::Transform(GameObject* owner)
{
	std::cout << "construct Transform of " << owner->name << std::endl;
	_owner = owner;
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

Transform::Transform(Transform const & src, GameObject* owner)
{
	std::cout << "construct Transform of " << owner->name << std::endl;
	_owner = owner;
	*this = src;
}

Transform::~Transform(void)
{
	std::cout << "destruct Transform" << std::endl;
}

// OVERLOADS //

Transform		&Transform::operator=(Transform const & rhs)
{
	position = rhs.position; 
	rotation = rhs.rotation;
	scale = rhs.scale;
	parent = rhs.parent;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Transform const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Transform::CalculateTransform() 
{ 
	_local = glm::mat4(1.0);
	_world = glm::mat4(1.0);
    _world = glm::translate(_world, position);

	_local = glm::rotate(_local, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	_local = glm::rotate(_local, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	_local = glm::rotate(_local, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

   	_local = glm::scale(_local, scale);
	_transform = _world * _local;
}

std::string		Transform::toString(void) const
{
	std::stringstream ss;
	ss 	<< "# Component Transform #" << std::endl;
	ss	<< "Position(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
	ss	<< "Rotation (" << rotation.x << "," << rotation.y << "," << rotation.z << ")" << std::endl;
	ss	<< "Scale (" << scale.x << "," << scale.y << "," << scale.z << ")" << std::endl;
	ss	<< "Parent : ";
	if (!parent)
		ss 	<< "None" << std::endl;
	else 
		ss 	<< parent->_owner->name << std::endl;
	return ss.str();
}

void			Transform::Save(std::ofstream &file)
{
	file << "\t\t\tTRANSFORM : " << std::endl;
	file	<< "POS : " << position.x << " " << position.y << " " << position.z << std::endl;
	file	<< "ROT : " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
	file	<< "SCALE : " << scale.x << " " << scale.y << " " << scale.z << std::endl;
	file	<< "Parent : ";
	if (!parent)
		file 	<< "" << std::endl;
	else 
		file 	<< parent->_owner->name << std::endl;
}

// PRIVATE //


// GETTER SETTER //

GameObject*		Transform::GetOwner() { return _owner; }
glm::mat4		Transform::GetTransform() { return _transform; }