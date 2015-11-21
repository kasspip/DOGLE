#include "Physics.hpp"
#include "Script.hpp"
#include "Engine.hpp"

// CONSTRUCTOR DESTRUCTOR //

Physics	*Physics::singleton = nullptr;


glm::vec3		Physics::btVector3ToGlmVec3(btVector3 v)
{
	return (glm::vec3(v.x(), v.y(), v.z()));
}

btVector3		Physics::GlmVec3TobtVector3(glm::vec3 v)
{
	return (btVector3(v.x, v.y, v.z));
}

btQuaternion	Physics::euler123_to_quaternion(glm::vec3 &v)
{

	float c1 = cos(v.x / 2);
	float s1 = sin(v.x / 2);
	float c2 = cos(v.y / 2);
	float s2 = sin(v.y / 2);
	float c3 = cos(v.z / 2);
	float s3 = sin(v.z / 2);

	return (btQuaternion(
		c1 * c2 * c3 - s1 * s2 * s3,
		s1 * c2 * c3 + c1 * s2 * s3,
		c1 * s2 * c3 - s1 * c2 * s3,
		c1 * c2 * s3 + s1 * s2 * c3
		));
}

glm::vec3		Physics::quaternion_to_euler123(btQuaternion &q)
{
	return (glm::vec3(
		atan2(-2 * (q.y() * q.z() - q.w() * q.x()), q.w() * q.w() - q.x() * q.x() - q.y() * q.y() + q.z() * q.z()),
		asin(2 * (q.x() * q.z() + q.w() * q.y())),
		atan2(-2 * (q.x() *q.y() - q.w() * q.z()), q.w() * q.w() + q.x() * q.x() - q.y() * q.y() - q.z() * q.z())
		));
}


void	*Physics::CreatePhysic(GameObject *go, Collider *collider)
{
	if (!collider)
		return (nullptr);
	Transform	*transform = go->GetComponent<Transform>();


	btCollisionShape* colShape = new btBoxShape(btVector3(collider->size.x,collider->size.y,collider->size.y));
	colShape->setLocalScaling(GlmVec3TobtVector3(transform->GetScale()));

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(GlmVec3TobtVector3(transform->GetPosition() + collider->center));
	btQuaternion	tmp_q;
	glm::vec3		rot = transform->GetRotation();
	tmp_q.setEuler(rot.x, rot.y, rot.z);
	startTransform.setRotation(tmp_q);

	btScalar	mass(collider->mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass,localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setUserPointer(go);
	_dynamicsWorld->addRigidBody(body);
	return (body);
}

Physics::Physics(void)
{
	singleton = this;
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_overlappingPairCache = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver();
	_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);
	_dynamicsWorld->setGravity(btVector3(0,-10,0));

}

void	Physics::DestroyPhysic(btCollisionObject	*obj)
{
	btCollisionShape	*shape = obj->getCollisionShape();
	btRigidBody* body = btRigidBody::upcast(obj);
	if (shape)
		delete shape;
	if (body && body->getMotionState())
	{
		
		delete body->getMotionState();
	}
	_dynamicsWorld->removeCollisionObject( obj );
	delete obj;
}

Physics::~Physics(void)
{
	singleton = nullptr;
	int i;

	for (i=_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = _dynamicsWorld->getCollisionObjectArray()[i];
		DestroyPhysic(obj);
	}

	delete _collisionConfiguration;
	delete _dispatcher;
	delete _overlappingPairCache;
	delete _solver;
	delete _dynamicsWorld;
}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Physics const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Physics::CallCollision()
{
	int numManifolds = _dynamicsWorld->getDispatcher()->getNumManifolds();
	
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  _dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject	*obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
		const btCollisionObject	*obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
		GameObject				*go1 = static_cast<GameObject *>(obA->getUserPointer());
		GameObject				*go2 = static_cast<GameObject *>(obB->getUserPointer());

		Script			*script = nullptr;
		for (IComponent* compo : go1->GetListComponent())
		{
			if ((script = dynamic_cast<Script*>(compo)))
			{
				script->OnCollisionEnter(go2);
				script = nullptr;
			}
		}
		for (IComponent* compo : go2->GetListComponent())
		{
			if ((script = dynamic_cast<Script*>(compo)))
			{
				script->OnCollisionEnter(go1);
				script = nullptr;
			}
		}
	}
}

void			Physics::RunState(Application & app, e_state & currentState)
{

	PRINT_DEBUG("[MACHINE] <Physics>");
	(void)app;

	float currentFrame = glfwGetTime();
	Engine::singleton->deltaTime = currentFrame - Engine::singleton->lastFrame;
	Engine::singleton->lastFrame = currentFrame;

	_dynamicsWorld->stepSimulation(Engine::singleton->deltaTime, 10);

	int numCollisionObjects = _dynamicsWorld->getNumCollisionObjects();
	for (int i = 0; i<numCollisionObjects; i++)
	{
		btCollisionObject	*colObj = _dynamicsWorld->getCollisionObjectArray()[i];
		btVector3			pos = colObj->getWorldTransform().getOrigin();
		btQuaternion		orn = colObj->getWorldTransform().getRotation();
		GameObject			*go = static_cast<GameObject *>(colObj->getUserPointer());
		Collider			*collider = go->GetComponent<Collider>();
		btRigidBody			*rigid = btRigidBody::upcast(colObj);
		if (collider)
		{
			if (collider->force != glm::vec3())
			{
				rigid->activate(true);
				btVector3 tmp_v = rigid->getLinearVelocity();
				rigid->setLinearVelocity(btVector3(collider->force.x, tmp_v.y(), collider->force.z));
			}
			if (collider->impulse != glm::vec3())
			{
				rigid->activate(true);
				std::cout << "JUMP" << std::endl;
				rigid->applyCentralImpulse(btVector3(collider->impulse.x, collider->impulse.y, collider->impulse.z));
				collider->impulse = glm::vec3();
			}
		}
		if (go)
		{
			//go->GetComponent<Transform>()->_rotation = quaternion_to_euler123(orn);
			go->GetComponent<Transform>()->_position = btVector3ToGlmVec3(pos);
		}
	}
	currentState = STATE_INPUTS;
}

std::string		Physics::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

// GETTER SETTER //
