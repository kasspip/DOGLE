#include "Transform.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Transform::Transform()
{
	std::cout << "construct Transform " << std::endl;
	name = "Transform";
	
	position = glm::vec3(0.0, 0.0, 0.0);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc)
{
	name = "Transform";
	position = pos;
	rotation = rot;
	scale = sc;
}


Transform::Transform(Transform const & src)
{
	name = "Transform";
	std::cout << "construct Transform " << std::endl;
	*this = src;
}

Transform::~Transform(void)
{
	std::cout << "destruct Transform" << std::endl;
}

// OVERLOADS //

Transform       &Transform::operator=(Transform const & rhs)
{
	position = rhs.position; 
	rotation = rhs.rotation;
	scale = rhs.scale;
	return *this;
}

std::ostream    &operator<<(std::ostream & o, Transform const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

glm::mat4            Transform::CalculateTransform()
{ 
	if (gameObject->GetParent() == nullptr)
	{
		_local = glm::mat4(1.0);
		_local = glm::rotate(_local, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_local = glm::rotate(_local, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_local = glm::rotate(_local, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		_local = glm::scale(_local, scale);

		_world = glm::mat4(1.0);
		_world = glm::translate(_world, position);
		return _world * _local;
	}
	else
	{
		_local = glm::mat4(1.0);
		_local = glm::rotate(_local, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_local = glm::rotate(_local, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_local = glm::rotate(_local, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		_local = glm::scale(_local, scale);

		glm::vec3 pos = position;
		pos.z *= -1;
		_world = glm::mat4(1.0);
		_world = glm::translate(_world, pos);
		
		// update pos,rot,scale
		
		return gameObject->GetParent()->GetComponent<Transform>()->CalculateTransform() * (_world * _local);
	}
}

std::string     Transform::toString(void) const
{
	std::stringstream ss;
	ss  << "# Component Transform #" << std::endl;
	ss  << "Position(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
	ss  << "Rotation (" << rotation.x << "," << rotation.y << "," << rotation.z << ")" << std::endl;
	ss  << "Scale (" << scale.x << "," << scale.y << "," << scale.z << ")" << std::endl;
	return ss.str();
}

void            Transform::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
		TABS = "\t\t\t";
	file << TABS << "TRANSFORM:" 
	<< position.x   << SEPARATOR_F << position.y    << SEPARATOR_F << position.z 	<< SEPARATOR
	<< rotation.x   << SEPARATOR_F << rotation.y    << SEPARATOR_F << rotation.z 	<< SEPARATOR
	<< scale.x      << SEPARATOR_F << scale.y       << SEPARATOR_F << scale.z 		<< std::endl;
}

// PRIVATE //


// GETTER SETTER //

glm::mat4       Transform::GetMatrice() 
{
	return CalculateTransform(); 
}