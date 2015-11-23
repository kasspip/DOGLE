#ifndef SCENE_HPP
# define SCENE_HPP

# include "DOGLE.hpp"
# include "GameObject.hpp"

	class Scene
	{
		static size_t	counter;
		
		public:

			Scene(void);
			Scene(std::string);
			~Scene(void);
			
			std::string 			toString(void) const;
			void					Save(std::ofstream &file);
			GameObject*				InstanciatePrefab(GameObject *prefab);
			GameObject*				InstanciatePrefab(GameObject *prefab, Transform tr);
			void					DeleteInstance(std::string name);
			GameObject*				AddGameObject(GameObject* go);

			GameObject*				FindGameObject(std::string name);
			std::list<GameObject*>	&GetGameObjectList(void);
			std::list<GameObject*>	&GetBindGameObjectList(void);

			std::string				name;

		private:
			Scene(Scene const &src);
			Scene &operator=(Scene const &rhs);

			size_t					_id;
			std::list<GameObject*>	_listGameObject;
			std::list<GameObject*>	_listBindGameObject;
			GameObject*				_currentCamera;
	};

	std::ostream	&operator<<(std::ostream &o, Scene const &rhs);

#endif
