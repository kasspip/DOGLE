#ifndef APPLICATIONCLASS_HPP
# define APPLICATIONCLASS_HPP

# include "DOGLE.hpp"
# include "Scene.hpp"
# include "GameObject.hpp"
# include "Skin.hpp"

	class Application
	{
		public:

			Application(void);
			Application(std::string);
			~Application(void);
		
			
			std::string 	toString(void) const;
			void			Save(void);

			// Prefab
			void			AddPrefab(GameObject* gameObject);
			GameObject*		FindPrefab(std::string name);

			//	Scene
			void			AddScene(Scene* scene);
			Scene*			FindScene(std::string name);
			void			LoadScene(Scene* scene);
			Scene*			GetCurrentScene(void);

			// Engine
			GLFWwindow			*window;
			GLuint				shaderProgram3D;
			GLuint				shaderProgramDebug;
			bool				appShouldClose;
			

			// Custom
			std::string			name;
			int					winW;
			int					winH;

		private:

			Application(Application const &src);
			Application &operator=(Application const &rhs);

			std::list<GameObject*>	_listPrefab;
			std::list<Scene*>		_listScene;
			Scene*					_currentScene;

			void		_SkinVBO(Skin & skin);
			void		_BindBuffer(GLfloat *data, GLuint dateSize, GLuint *id);
			void		_BindAttribut(GLuint bufferId, GLuint attributId, int pSize);
			void		_SkinVAO(Skin& skin);
	};

	std::ostream	&operator<<(std::ostream &o, Application const &rhs);

#endif
