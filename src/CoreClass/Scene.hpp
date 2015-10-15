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
			void					InstanciatePrefab(GameObject *prefab);
			GameObject*				FindGameObject(std::string name);
			std::list<GameObject*>	GetGameObjectList(void) const;
			GameObject*				GetCurrentCamera() const;
			void					SetCurrentCamera(GameObject* go);
			
			std::string				name;

		private:
			Scene(Scene const &src);
			Scene &operator=(Scene const &rhs);

			size_t					_id;
			std::list<GameObject*>	_listGameObject;
			GameObject*				_currentCamera;
	};

	std::ostream	&operator<<(std::ostream &o, Scene const &rhs);

#endif
