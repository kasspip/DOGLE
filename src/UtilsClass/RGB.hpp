
#ifndef RGB_HPP
# define RGB_HPP

# include "DOGLE.hpp"

	class RGB
	{
		public:

			RGB(float, float, float, float);
			RGB(u_char, u_char, u_char, u_char);
			RGB(RGB const &src);
			~RGB(void);
		
			RGB &operator=(RGB const &rhs);
			std::string toString(void) const;
			float 	n_r;
			float 	n_g;
			float 	n_b;
			float	n_a;
			u_char	r;
			u_char	g;
			u_char	b;
			u_char	a;

		private:
			RGB(void);
			void	_normalize(void);
			void	_unormalize(void);

	};

	std::ostream	&operator<<(std::ostream &o, RGB const &rhs);

#endif
