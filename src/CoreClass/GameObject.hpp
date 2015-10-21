#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "DOGLE.hpp"
# include "Transform.hpp"
# include "Skin.hpp"
# include "Camera.hpp"
# include "Light.hpp"

	class IComponent;

	class GameObject
	{
		static size_t	counter;

		public:

			GameObject(std::string name = _GetDefaultName());
			GameObject(GameObject const &src);
			~GameObject(void);

			GameObject &operator=(GameObject const &rhs);

			void						Save(std::ofstream &file);
			void						AddComponent(IComponent *cmp);
			std::string 				toString(void);
			std::list<IComponent*>		GetListComponent() const;

			template < typename T > T*	GetComponent(void)
			{
				std::list<IComponent*>::iterator it = _listComponent.begin();
				for (; it != _listComponent.end(); it++)
				{
					if (dynamic_cast<T*>(*it))
						return dynamic_cast<T*>(*it);
				}
				return nullptr;
			}

			std::string				name;

			bool						GetDestroy();
			void						SetDestroy(bool set);
			bool						IsPrefab();

		private:

		GameObject(void);
		static std::string				_GetDefaultName();

		bool					_isPrefab;
		size_t					_id;
		std::list<IComponent*>	_listComponent;
		bool					_destroyMe;

	};

	std::ostream	&operator<<(std::ostream &o, GameObject &rhs);

#endif
