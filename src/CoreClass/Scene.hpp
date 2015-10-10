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
			Scene(Scene const &src);
			~Scene(void);
		
			Scene &operator=(Scene const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);
			void		AddGameObject(GameObject *gameObject);

		private:
			size_t					_id;
			std::string				_name;
			std::list<GameObject *>	_listGameObject;

	};

	std::ostream	&operator<<(std::ostream &o, Scene const &rhs);

#endif
