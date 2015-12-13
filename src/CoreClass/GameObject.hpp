#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "DOGLE.hpp"
# include "Transform.hpp"
# include "Skin.hpp"
# include "Collider.hpp"
# include "Camera.hpp"
# include "Light.hpp"
# include "Text.hpp"

class IComponent;
class Script;

	class GameObject
	{
		public:

			GameObject(std::string name = _GetDefaultName());
			GameObject(GameObject const &src);
			~GameObject(void);

			GameObject&					operator=(GameObject const &rhs);

			void						Save(std::ofstream &file);
			void						AddComponent(IComponent *cmp);
			void						DeleteComponent(std::string name);
			std::string 				toString(void);
			void						SetParent(GameObject* go);
			GameObject*					GetParent();
			bool						GetDestroy();
			void						SetDestroy(bool val);
			bool						IsPrefab();
			void						SetIsPrefab(bool val);
			Script*						GetScript(std::string name);

			template < typename T > T*	GetComponent(void)
			{
				for (IComponent* compo : _listComponent)
				{
					if (dynamic_cast<T*>(compo))
						return dynamic_cast<T*>(compo);
				}
				return nullptr;
			}

			template < typename T > std::list<T*>	GetComponents(void)
			{
				std::list<T*> ret;
				for (IComponent* compo : _listComponent)
				{
					if (dynamic_cast<T*>(compo))
						ret.push_back( dynamic_cast<T*>(compo) );
				}
				return ret;
			}

			std::string					name;
			std::list<IComponent*>			_listComponent;

		private:

			GameObject(void);

			static std::string				_GetDefaultName();
			static size_t					_counter;
			bool							_isPrefab;
			size_t							_id;
			bool							_destroyMe;
			GameObject*						_parentObject;
	};

	std::ostream	&operator<<(std::ostream &o, GameObject &rhs);

#endif
