#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "DOGLE.hpp"
# include "IState.hpp"
# include "btBulletDynamicsCommon.h"
# include "Collider.hpp"

	class Physics : public IState
	{
		public:

			Physics(void);
			~Physics(void);
		
			std::string toString(void) const;
			void		RunState(Application & app, e_state	& currentState);
			void		*CreatePhysic(GameObject *go, Collider *collider);
			void		DestroyPhysic(btCollisionObject	*obj);
			void		CallCollision();
			void		InstantiateGo(void* body);

			static Physics	*singleton;

			static glm::vec3		btVector3ToGlmVec3(btVector3 v);
			static btVector3		GlmVec3TobtVector3(glm::vec3 v);
			static btQuaternion		euler123_to_quaternion(glm::vec3 &v);
			static glm::vec3		quaternion_to_euler123(btQuaternion &q);

		private:

			Physics &operator=(Physics const &rhs);
			Physics(Physics const &src);


			btDefaultCollisionConfiguration		*_collisionConfiguration;
			btCollisionDispatcher				*_dispatcher;
			btBroadphaseInterface				*_overlappingPairCache;
			btSequentialImpulseConstraintSolver	*_solver;
			btDiscreteDynamicsWorld				*_dynamicsWorld;
	};

	std::ostream	&operator<<(std::ostream &o, Physics const &rhs);

#endif
