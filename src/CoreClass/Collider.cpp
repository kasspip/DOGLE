#include "Collider.hpp"
#include <limits> 
#include <algorithm>
#include "GameObject.hpp"
#include "Physics.hpp"

// CONSTRUCTOR DESTRUCTOR //

Collider::Collider(glm::vec3 pos, glm::vec3 sz, bool b, float massf) : center(pos), size(sz), enable(b), mass(massf), impulse(glm::vec3()), force(glm::vec3()), _skinned(false)
{
	std::cout << "construct Collider withoud skin" << std::endl;
	type = "Collider";
	physic_ptr = nullptr;
	isPhy = false;
}

Collider::Collider(GameObject *go, bool b, float massf) : enable(b), mass(massf), impulse(glm::vec3()), force(glm::vec3()), _skinned(true)
{
	std::cout << "construct Collider with skin" << std::endl;
	type = "Collider";

	Skin			*skin = go->GetComponent<Skin>();
	const GLfloat	min_f = std::numeric_limits<float>::min();
	const GLfloat	max_f = std::numeric_limits<float>::max();
	glm::vec3		min_vec(max_f, max_f, max_f);
	glm::vec3		max_vec(min_f, min_f, min_f);

	for (unsigned int i = 0; i < skin->nb_vertices; i = ++i)
	{
		min_vec.x = std::min(skin->positions[i * 3], min_vec.x);
		max_vec.x = std::max(skin->positions[i * 3], max_vec.x);
		min_vec.y = std::min(skin->positions[i * 3 + 1], min_vec.y);
		max_vec.y = std::max(skin->positions[i * 3 + 1], max_vec.y);
		min_vec.z = std::min(skin->positions[i * 3 + 2], min_vec.z);
		max_vec.z = std::max(skin->positions[i * 3 + 2], max_vec.z);

	}
	center = (max_vec + min_vec) / 2.0f;
	size = max_vec - center;
	physic_ptr = Physics::singleton->CreatePhysic(go, this);
	std::cout << toString();
	isPhy = false;
}

Collider::~Collider(void)
{
	std::cout << "destruct Collider " << std::endl;
	if (physic_ptr)
		Physics::singleton->DestroyPhysic(static_cast<btCollisionObject	*>(physic_ptr));
}

// OVERLOADS //

Collider	&Collider::operator=(Collider const & rhs) //instable
{
	center = rhs.center;
	size = rhs.size;
	enable = rhs.enable;
	mass = rhs.mass;
	impulse = glm::vec3();
	force = glm::vec3();
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Collider const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Collider::toString(void) const
{
	std::stringstream ss;
	ss  << "# Component Collider #" << std::endl;
	ss  << "center(" << center.x << "," << center.y << "," << center.z << ")" << std::endl;
	ss  << "Size(" << size.x << "," << size.y << "," << size.z << ")" << std::endl;
	ss  << "Enable : " <<  enable << std::endl;
	ss  << "Mass : " <<  mass << std::endl;
	return ss.str();
}

void		Collider::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
	 	TABS = "\t\t\t";
	file << TABS << "COLLIDER:";
	// if (_skinned == false)
	// { 
	// 	file << center.x << SEPARATOR_F << center.y << SEPARATOR_F << center.z << SEPARATOR
	// 		 << size.x << SEPARATOR_F << size.y << SEPARATOR_F << size.z << SEPARATOR;
	// }
	if (enable)
		file << "true" << SEPARATOR;
	else
		file << "false" << SEPARATOR;
	file << mass << std::endl;

}

void		Collider::ForgivePhysicRotation()
{
	static_cast<btRigidBody *>(physic_ptr)->setAngularFactor(btVector3(0,0,0));
}

bool		Collider::IsSkinned() { return _skinned; }


// PRIVATE //

// GETTER SETTER //
