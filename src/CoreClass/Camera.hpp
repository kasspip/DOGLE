#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

	class Camera : public IComponent
	{
		public:

			Camera(void);
			Camera(Camera const &src);
			~Camera(void);
		
			Camera &operator=(Camera const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, Camera const &rhs);

#endif
