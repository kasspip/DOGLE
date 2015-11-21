#ifndef ICOMPONENT_HPP
# define ICOMPONENT_HPP

# include "DOGLE.hpp"


	class GameObject;
	class Transform;

	class IComponent
	{
		public:
			virtual ~IComponent(void){};
			virtual void		Save(std::ofstream &file) = 0;
			virtual std::string toString(void) const = 0;

			Transform			*transform;
			GameObject			*gameObject;

		private:

	};

#endif
