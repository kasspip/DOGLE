#include "RGB.hpp"

// CONSTRUCTOR DESTRUCTOR //

RGB::RGB(float r, float g , float b, float a) : n_r(r),
												n_g(g),
												n_b(b),
												n_a(a)
{
	_unormalize();
}

RGB::RGB(u_char r, u_char g , u_char b, u_char a) : r(r),
													g(g),
													b(b),
													a(a)
{
	_normalize();
}

RGB::RGB(RGB const & src)
{
	*this = src;
}

RGB::~RGB(void){}

// OVERLOADS //

RGB	&RGB::operator=(RGB const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, RGB const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		RGB::toString(void) const
{
	std::stringstream ss;
	ss << r << "." << g << "." << b << "." << a;
	return ss.str();
}

// PRIVATE //
void			RGB::_normalize(void)
{
	n_r = r / 255;
	n_g = g / 255;
	n_b = b / 255;
	n_a = a / 255;
}

void			RGB::_unormalize(void)
{
	r = n_r * 255;
	g = n_g * 255;
	b = n_b * 255;
	a = n_a * 255;
}

// GETTER SETTER //
