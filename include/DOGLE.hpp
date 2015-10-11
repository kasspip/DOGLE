#ifndef DOGLE_HPP
#define DOGLE_HPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <ctime>
# include <list>
# include <vector>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <SOIL2.h>
# include <fcntl.h>
# include <string.h>

# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"
# include "glm/gtc/type_ptr.hpp"
# include "Error.hpp" 

# define C_YELLOW  "\x1B[33m"
# define C_GREEN  "\x1B[32m"
# define C_DEFAULT "\x1B[0m"

typedef enum	state
{
	INITIALISATION,
	EXIT,
	STATE_NBR
}				e_state;

#endif
