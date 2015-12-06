#include "Transform.hpp"
#include "GameObject.hpp"
#include "Physics.hpp"
// CONSTRUCTOR DESTRUCTOR //

Transform::Transform()
{
	std::cout << "construct Transform of " << std::endl;
	type = "Transform";
	_position = glm::vec3(0.0, 0.0, 0.0);
	_rotation = glm::vec3(0.0f);
	_scale = glm::vec3(1.0f);
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc)
{
	type = "Transform";
	_position = pos;
	_rotation = rot;
	_scale = sc;
}


Transform::Transform(Transform const & src)
{
	std::cout << "construct Transform " << std::endl;
	type = "Transform";
	*this = src;
}

Transform::~Transform(void)
{
	std::cout << "destruct Transform" << std::endl;
}

// OVERLOADS //

Transform       &Transform::operator=(Transform const & rhs)
{
	_position = rhs._position; 
	_rotation = rhs._rotation;
	_scale = rhs._scale;
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
		_local = glm::rotate(_local, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_local = glm::rotate(_local, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_local = glm::rotate(_local, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		_local = glm::scale(_local, _scale);

		_world = glm::mat4(1.0);
		_world = glm::translate(_world, _position);
		return _world * _local;
	}
	else
	{
		_local = glm::mat4(1.0);
		_local = glm::rotate(_local, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_local = glm::rotate(_local, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_local = glm::rotate(_local, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		_local = glm::scale(_local, _scale);

		glm::vec3 pos = _position;
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
	ss  << "Position(" << _position.x << "," << _position.y << "," << _position.z << ")" << std::endl;
	ss  << "Rotation (" << _rotation.x << "," << _rotation.y << "," << _rotation.z << ")" << std::endl;
	ss  << "Scale (" << _scale.x << "," << _scale.y << "," << _scale.z << ")" << std::endl;
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
	<< _position.x   << SEPARATOR_F << _position.y    << SEPARATOR_F << _position.z 	<< SEPARATOR
	<< _rotation.x   << SEPARATOR_F << _rotation.y    << SEPARATOR_F << _rotation.z 	<< SEPARATOR
	<< _scale.x      << SEPARATOR_F << _scale.y       << SEPARATOR_F << _scale.z 		<< std::endl;
}

// PRIVATE //


// GETTER SETTER //

glm::mat4       Transform::GetMatrice() 
{
	return CalculateTransform(); 
}

glm::vec3	Transform::GetPosition() const
{
	return (_position);
}

glm::vec3	Transform::GetRotation() const
{
	return (_rotation);
}

glm::vec3	Transform::GetScale() const
{
	return (_scale);
}


glm::vec3	Transform::Forward() const
{
	const float DEG2RAD =  1;//3.141593f / 180;
	float sx, sy, sz, cx, cy, cz, theta;

	// rotation angle about X-axis (pitch)
	theta = _rotation.x * DEG2RAD;
	sx = sinf(theta);
	cx = cosf(theta);

	// rotation angle about Y-axis (yaw)
	theta = _rotation.y * DEG2RAD;
	sy = sinf(theta);
	cy = cosf(theta);

	// rotation angle about Z-axis (roll)
	theta = _rotation.z * DEG2RAD;
	sz = sinf(theta);
	cz = cosf(theta);


	return (glm::normalize(glm::vec3(sy,
		-sx*cy,
		cx*cy)));
}

glm::vec3	Transform::Left() const
{
	const float DEG2RAD = 1;// 3.141593f / 180;
	float sx, sy, sz, cx, cy, cz, theta;

	// rotation angle about X-axis (pitch)
	theta = _rotation.x * DEG2RAD;
	sx = sinf(theta);
	cx = cosf(theta);

	// rotation angle about Y-axis (yaw)
	theta = _rotation.y * DEG2RAD;
	sy = sinf(theta);
	cy = cosf(theta);

	// rotation angle about Z-axis (roll)
	theta = _rotation.z * DEG2RAD;
	sz = sinf(theta);
	cz = cosf(theta);

	return (glm::normalize(glm::vec3(cy*cz,
		sx*sy*cz + cx*sz,
		-cx*sy*cz + sx*sz)));
}

glm::vec3	Transform::Up() const
{
	const float DEG2RAD = 1;//3.141593f / 180;
	float sx, sy, sz, cx, cy, cz, theta;

	// rotation angle about X-axis (pitch)
	theta = _rotation.x * DEG2RAD;
	sx = sinf(theta);
	cx = cosf(theta);

	// rotation angle about Y-axis (yaw)
	theta = _rotation.y * DEG2RAD;
	sy = sinf(theta);
	cy = cosf(theta);

	// rotation angle about Z-axis (roll)
	theta = _rotation.z * DEG2RAD;
	sz = sinf(theta);
	cz = cosf(theta);

	return (glm::normalize(glm::vec3(-cy*sz,
		-sx*sy*sz + cx*cz,
		cx*sy*sz + sx*cz)));
}

void		Transform::_SetPhysicPosition()
{
	Collider			*coll;
	btRigidBody			*rigid;

	if (!(coll  = gameObject->GetComponent<Collider>()) || !(rigid = static_cast<btRigidBody *>(coll->physic_ptr)))
		return ;
	rigid->getWorldTransform().setOrigin(Physics::GlmVec3TobtVector3(_position));
}



void		Transform::_SetPhysicRotation()
{
	Collider			*coll;
	btRigidBody			*rigid;
	btQuaternion		rot;

	if (!(coll  = gameObject->GetComponent<Collider>()) || !(rigid = static_cast<btRigidBody *>(coll->physic_ptr)))
		return ;
	//rot.setEuler(_rotation.y, _rotation.x, _rotation.z);
	btMatrix3x3 m2;
	btQuaternion q = btQuaternion(_rotation.y, _rotation.x, _rotation.z);
	m2.setRotation(q);
	rigid->getWorldTransform().setBasis(m2);
}

void		Transform::_SetPhysicScale()
{
	Collider			*coll;
	btRigidBody			*rigid;
	btCollisionShape	*colShape;

	if (!(coll  = gameObject->GetComponent<Collider>()) || !(rigid = static_cast<btRigidBody *>(coll->physic_ptr)) ||
		!(colShape = rigid->getCollisionShape()))
		return ;
	colShape->setLocalScaling(Physics::GlmVec3TobtVector3(_scale));
}

void		Transform::SetPosition(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
	_SetPhysicPosition();
}

void		Transform::SetRotation(float x, float y, float z)
{
	_rotation = glm::vec3(x, y, z);
	_SetPhysicRotation();
}

void		Transform::SetScale(float x, float y, float z)
{
	_scale = glm::vec3(x, y, z);
	_SetPhysicScale();
}

void		Transform::SetPosition(glm::vec3 v)
{
	_position = v;
	_SetPhysicPosition();
}

void		Transform::SetRotation(glm::vec3 v)
{
	_rotation = v;
	_SetPhysicRotation();
}

void		Transform::SetScale(glm::vec3 v)
{
	_scale = v;
	_SetPhysicScale();
}


