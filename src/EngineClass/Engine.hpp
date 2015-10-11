#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "DOGLE.hpp"
# include "StateMachine.hpp"

	class Engine
	{
		public:
			Engine(void);
			~Engine(void);
			Engine &operator=(Engine const &rhs);
			
			std::string toString(void) const;
			void		StartOpenGL(void);
			void		StopOpenGL(void);
			void		RunApplication(Application & app);

		private:
			Engine(Engine const &src);

			Application		*_app;
			StateMachine	_SM;

			// openGL
			bool			_setupOpenGL;
			GLFWwindow		*_window;
			int				_winW;
			int				_winH;



			// Opengl settings
			const GLubyte	*_renderer;
			const GLubyte	*_version;
			int				_versionMajor;
			int				_versionMinor;
			int				_aliasingSamples;

			// shaders
			GLuint			_3DShaderProgram;

			void			_CompileShader(std::string name);
			const char 		*_GetShaderCode(std::string filePath);


	};

	std::ostream	&operator<<(std::ostream &o, Engine const &rhs);

#endif
