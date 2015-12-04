#include "Text.hpp"
#include "GameObject.hpp"

std::string		Text::pathToFont = "resources/Fonts/";


// CONSTRUCTOR DESTRUCTOR //

Text::Text(std::string txt, int sz, std::string txtFont)
{
	std::cout << "Construct Text" << std::endl;
	type = "Text";
	text = txt;
	font = txtFont;
	size = sz;

	if(FT_Init_FreeType(&_freetype))
		throw DError() << msg("Could not init freetype library");
	if(FT_New_Face(_freetype, (pathToFont + txtFont).c_str(), 0, &_face))
		throw DError() << msg("Could not open font: " + txtFont);
	FT_Set_Pixel_Sizes(_face, 0, size);
}

Text::Text(Text const & src)
{
	std::cout << "Construct Text" << std::endl;
	type = "Text";
	*this = src;
}

Text::~Text(void)
{
	std::cout << "Destruct Text" << std::endl;
}

// OVERLOADS //

Text	&Text::operator=(Text const & rhs)
{
	text = rhs.text;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Text const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		Text::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Text #" << std::endl
	<< "Text : " << text ;
	return ss.str();
}

void			Text::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
	 	TABS = "\t\t\t";
	file 	<< TABS << "TEXT:" 
			<< text << SEPARATOR << size << SEPARATOR << font
			<< std::endl;
}

// PRIVATE //

// GETTER SETTER //