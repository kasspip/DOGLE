#ifndef TEXT_HPP
# define TEXT_HPP

# include "DOGLE.hpp"
# include "Shader.h"
# include "IComponent.hpp"

	class Text : public IComponent
	{
		public:

			struct Character
			{
			    GLuint TextureID;
			    glm::ivec2 Size; 
			    glm::ivec2 Bearing;
			    GLuint Advance;
			};

			static std::string		pathToFont;
			static std::string		pathToShaders;

			Text(std::string txt = "empty text", int size = 48, std::string txtFont = "Arial.ttf",
				 GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1, glm::vec3 color = glm::vec3(0,0,0));
			Text(Text const &src);
			~Text(void);
		
			Text &operator=(Text const &rhs);
			
			std::string toString(void) const;
			void		Save(std::ofstream &file);
			void		LoadFont(GLfloat width, GLfloat height);
			void		RenderText();
 			
  			bool		isInit;
			std::map<GLchar, Character> Characters;
			int 		size;

			// script alterable
			std::string text;
			GLfloat		x;
			GLfloat		y;
			GLfloat		scale;
			glm::vec3 	color;

		private:
			Text(void);
			std::string font;
  			Shader*		shader;

			GLuint 		VAO;
			GLuint 		VBO;

			FT_Library 	freetype;
  			FT_Face 	face;
			glm::mat4 	projection;
	};

	std::ostream	&operator<<(std::ostream &o, Text const &rhs);

#endif