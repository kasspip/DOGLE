#ifndef TEXT_HPP
# define TEXT_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"

	class Text : public IComponent
	{
		public:

			static std::string		pathToFont;

			Text(std::string txt = "empty text", int size = 48, std::string txtFont = "Arial.ttf");
			Text(Text const &src);
			~Text(void);
		
			Text &operator=(Text const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);

			std::string text;
			std::string font;
			int 		size;

		private:
			Text(void);
			FT_Library 	_freetype;
  			FT_Face 	_face;
	};

	std::ostream	&operator<<(std::ostream &o, Text const &rhs);

#endif