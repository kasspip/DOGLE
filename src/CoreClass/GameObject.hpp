#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

	class GameObject
	{
		public:

			GameObject(void);
			GameObject(GameObject const &src);
			~GameObject(void);
		
			GameObject &operator=(GameObject const &rhs);
			
			std::string toString(void) const;
			void		AddComponent(IComponent *cmp);

		private:
		
		std::list<IComponent *>	_listComponent;
	};

	std::ostream	&operator<<(std::ostream &o, GameObject const &rhs);

#endif
