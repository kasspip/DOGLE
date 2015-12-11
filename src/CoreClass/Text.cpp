#include "Text.hpp"
#include "GameObject.hpp"

std::string		Text::pathToFont = "resources/Fonts/";
std::string		Text::pathToShaders = "resources/Shaders/";


// CONSTRUCTOR DESTRUCTOR //
Text::Text(std::string txt, int sz, std::string txtFont, GLfloat px, GLfloat py, GLfloat scl, glm::vec3 col)
{
	std::cout << "Construct Text" << std::endl;
	type = "Text";
	text = txt;
	font = txtFont;
	size = sz;
	x = px;
	y = py;
	scale = scl;
	color = col;
	isInit = false;
	shader = nullptr;
}

Text::Text(Text const & src)
{
	std::cout << "Construct Text" << std::endl;
	type = "Text";
    isInit = false;
    shader = nullptr;
	*this = src;
}

Text::~Text(void)
{
	std::cout << "Destruct Text" << std::endl;
    if (shader)
        delete shader;
}

// OVERLOADS //

Text	&Text::operator=(Text const & rhs)
{
	text = rhs.text;
	font = rhs.font;
	size = rhs.size;
	x = rhs.x;
	y = rhs.y;
	scale = rhs.scale;
	color = rhs.color;
    
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Text const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Text::LoadFont(GLfloat width, GLfloat height)
{
	shader = new Shader( (pathToShaders + "Text.vert").c_str(),
				  		 (pathToShaders + "Text.frag").c_str());
	shader->Use();
    glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height);
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	if(FT_Init_FreeType(&freetype))
		throw DError() << msg("Could not init freetype library");
	if(FT_New_Face(freetype, (pathToFont + font).c_str(), 0, &face))
		throw DError() << msg("Could not open font: " + font);
	
	FT_Set_Pixel_Sizes(face, 0, size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

	for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint)face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(freetype);

    
    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void 		Text::RenderText()
{
	if (!glIsEnabled(GL_BLEND))
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // Activate corresponding render state	
    shader->Use();
    glUniform3f(glGetUniformLocation(shader->Program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    GLfloat offset_x = x;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        GLfloat xpos = offset_x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }           
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        offset_x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

std::string		Text::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Text #" << std::endl
	<< "Text : " << text << std::endl
	<< "Size : " << size << std::endl
	<< "Font : " << font << std::endl
	<< "Position : " << x << " " << y << std::endl
	<< "Scale : " << scale << std::endl
	<< "Color : " << color.x << " " << color.y << " " << color.z << std::endl; 

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
			<< text << SEPARATOR 
			<< size << SEPARATOR 
			<< font << SEPARATOR
			<< x << SEPARATOR
			<< y << SEPARATOR
			<< scale << SEPARATOR
			<< color.x << SEPARATOR_F << color.y << SEPARATOR_F << color.z << SEPARATOR
			<< std::endl;
}

// PRIVATE //

// GETTER SETTER //