#ifndef APPLICATIONCLASS_HPP
# define APPLICATIONCLASS_HPP

# include "DOGLE.hpp"
# include "Scene.hpp"

	class Application
	{
		public:

			Application(void);
			Application(Application const &src);
			~Application(void);
		
			Application &operator=(Application const &rhs);
			
			std::string toString(void) const;
			void		AddScene(Scene *scene);

		private:
			std::list<Scene *> _listScene;
	
	};

	std::ostream	&operator<<(std::ostream &o, Application const &rhs);

#endif
