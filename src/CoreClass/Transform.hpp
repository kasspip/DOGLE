#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

	class Transform : public IComponent
	{
		public:

			Transform(void);
			Transform(Transform const &src);
			~Transform(void);
		
			Transform &operator=(Transform const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);

		private:
	
	};

	std::ostream	&operator<<(std::ostream &o, Transform const &rhs);

#endif
