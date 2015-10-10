#ifndef SCENE_HPP
# define SCENE_HPP

# include "DOGLE.hpp"
# include "GameObject.hpp"

	class Scene
	{
		public:

			Scene(void);
			Scene(Scene const &src);
			~Scene(void);
		
			Scene &operator=(Scene const &rhs);
			
			std::string toString(void) const;
			void	AddGameObject(GameObject *gameObject);

		private:
	
			std::list<GameObject *> _listGameObject;

	};

	std::ostream	&operator<<(std::ostream &o, Scene const &rhs);

#endif
