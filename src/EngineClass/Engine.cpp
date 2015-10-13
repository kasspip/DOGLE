#include "Engine.hpp"

// CONSTRUCTOR DESTRUCTOR //

Engine::Engine()
{
	_setupOpenGL = false;
	_app = NULL;
	// TODO from config file ?
	_winW = 1280;
	_winH = 1280;
	_versionMajor = 4;
	_versionMinor = 1;
	_aliasingSamples = 4;
	// end TODO
}

Engine::~Engine(void)
{

}

// OVERLOADS //

Engine	&Engine::operator=(Engine const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Engine const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Engine::RunApplication(Application & app)
{
	std::cout << "[ENGINE] <RunApplication> : " << app.name << std::endl;

	if (_app != NULL)
		delete _app;
	_app = &app;

	if (_setupOpenGL == false)
		throw DError() << msg("OpenGL is not setup. Use StartOpenGL().");
	app.ShaderProgram3D = _CompileShader("3D"); // shader par defaut ?
	_SM.RunApplication(app);
}


void			Engine::StartOpenGL(void)
{
	std::cout << std::endl << "[ENGINE] <StartOpenGL>" <<  std::endl;
	if (_setupOpenGL == true)
		return ;

	if (!glfwInit())
		throw DError() << msg("could not start GLFW3");
	// set hints version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _versionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window and GLFW context
	if ((_window = glfwCreateWindow(_winW, _winH, "GOGLE", NULL, NULL)) == NULL)
	{
		glfwTerminate();
		throw DError() << msg("glfw could not open window");
	}
	glfwMakeContextCurrent(_window);
	glewExperimental = GL_TRUE;
	glewInit();
	std::cout << "Renderer: " <<  (char*)glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported " <<  (char*)glGetString(GL_VERSION) << std::endl;

	// renderer attibuts
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0, 0.0, 0.0, 1);
	glfwWindowHint(GLFW_SAMPLES, _aliasingSamples);
	
	// culling mode
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// texture setting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	_setupOpenGL = true;
}

void			Engine::StopOpenGL(void)
{
	std::cout << "[ENGINE] <StopOpenGL>" << std::endl <<  std::endl;
	if (_app != NULL)
		delete _app;
	if (_setupOpenGL == true)
	{
		_setupOpenGL = false;
		glfwTerminate();
	}
}

std::string		Engine::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}


// PRIVATE //


const char 		*Engine::_GetShaderCode(std::string filePath)
{
	FILE 	*file;

	if ((file = fopen(filePath.c_str(), "r")) == NULL)
	{
		std::string error = "Shader File " + filePath + " not found.";
		throw DError() << msg(error);
	}
	int len = 0;
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *content = new char[len + 1];
	fread(content, len, 1, file);
	return (content);
}

GLuint			Engine::_CompileShader(std::string name)
{
	// get shaders code
	std::stringstream 	vertexFilePath; 
	std::stringstream 	fragmentFilePath;

	vertexFilePath << "resources/shaders/" << name << ".vert";
	fragmentFilePath << "resources/shaders/" << name << ".frag";
	const char * vertexCode = _GetShaderCode(vertexFilePath.str());
	const char * fragmentCode = _GetShaderCode(fragmentFilePath.str());

	// compile vertex shader code
	GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &(vertexCode), NULL);
	glCompileShader(vertexId);

	// compile fragment shader code
	GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &(fragmentCode), NULL);
	glCompileShader(fragmentId);
	
	// create shader program
	GLuint			ShaderProgram;
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexId);
	glAttachShader(ShaderProgram, fragmentId);
	glLinkProgram(ShaderProgram);

	// TOCHECK free vertexCode & fragmentCode & vertexId & fragmentId?
	return (ShaderProgram);
}

// GETTER SETTER //
