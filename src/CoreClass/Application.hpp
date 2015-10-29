#ifndef APPLICATIONCLASS_HPP
# define APPLICATIONCLASS_HPP

# include "DOGLE.hpp"
# include "Scene.hpp"
# include "GameObject.hpp"
# include "Skin.hpp"

	class Application
	{
		public:

			Application(std::string = "<AppName>", int width = 1280, int height = 1280);
			~Application(void);
					
			std::string 		toString(void) const;
			void				Save(void);

			// Prefab
			void				AddPrefab(GameObject* gameObject);
			GameObject*			FindPrefab(std::string name);

			//	Scene
			void				AddScene(Scene* scene);
			Scene*				FindScene(std::string name);
			void				LoadScene(Scene* scene);
			void				LoadScene(std::string name);
			void				Stop();

			std::list<GameObject*>	GetListPrefab();
			std::list<Scene*>	GetListScene();
			Scene*				GetCurrentScene(void);
			void				SetCurrentScene(Scene* scene);
			Scene*				GetSceneToLoad();
			bool				GetStop();

			// Engine
			GLFWwindow			*window;
			GLuint				shaderProgram3D;
			GLuint				shaderProgramDebug;
			Scene*				sceneToLoad;
			

			// Custom
			std::string			name;
			int					winW;
			int					winH;

			static Application	*singleton;

		private:
			
			Application(void);
			Application(Application const &src);
			Application &operator=(Application const &rhs);

			std::list<GameObject*>	_listPrefab;
			std::list<Scene*>		_listScene;
			Scene*					_currentScene;
			Scene*					_sceneToLoad;
			bool					_appShouldClose;
	};

	std::ostream	&operator<<(std::ostream &o, Application const &rhs);

#endif
