#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "DOGLE.hpp"
# include "StateMachine.hpp"
# include "Application.hpp"
# include "Script.hpp"

	class Engine
	{
		public:
			Engine(void);
			~Engine(void);
			Engine &operator=(Engine const &rhs);
			
			std::string toString(void) const;
			void		RunApplication(Application* app);
			void		Pause();

			static Engine*	singleton;
			bool			pause;
			
			// time
			float deltaTime;	// Time between current frame and last frame
			float lastFrame;	// Time of last frame

		private:
			Engine(Engine const &src);

			StateMachine	_SM;
			Application*	_app;

			// openGL
			int				_winW;
			int				_winH;
			bool			_setupOpenGL;
			GLFWwindow		*_window;
			void			_StartOpenGL(void);
			void			_StopOpenGL(void);

			// Opengl settings
			const GLubyte	*_renderer;
			const GLubyte	*_version;
			int				_versionMajor;
			int				_versionMinor;
			int				_aliasingSamples;

			// shaders
			GLuint			_CompileShader(std::string name);
			const char 		*_GetShaderCode(std::string filePath);


	};

	std::ostream	&operator<<(std::ostream &o, Engine const &rhs);

#endif
