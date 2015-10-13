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
			Application(Application const &src);
			~Application(void);
		
			Application &operator=(Application const &rhs);
			
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

			
			std::string			name;
			GLuint				ShaderProgram3D;
			bool				appShouldClose;
			GLFWwindow			*window;

		private:
			std::list<GameObject*>	_listPrefab;
			std::list<Scene*>		_listScene;
			Scene*					_currentScene;

			void		_SkinBindBuffers(Skin & skin);
	};

	std::ostream	&operator<<(std::ostream &o, Application const &rhs);

#endif
