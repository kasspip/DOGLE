#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

	class GameObject
	{
		static size_t	counter;

		public:

			GameObject(void);
			GameObject(std::string);
			GameObject(GameObject const &src);
			~GameObject(void);

			GameObject &operator=(GameObject const &rhs);

			std::string toString(void) const;
			void		Save(std::ofstream &file);
			void		AddComponent(IComponent *cmp);

		private:
		size_t					_id;
		std::string				_name;
		std::list<IComponent *>	_listComponent;
	};

	std::ostream	&operator<<(std::ostream &o, GameObject const &rhs);

#endif
