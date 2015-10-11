#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "DOGLE.hpp"
# include "StateMachine.hpp"

	class Engine
	{
		public:
			Engine(Application &app);
			~Engine(void);
			Engine &operator=(Engine const &rhs);
			
			std::string toString(void) const;

		private:
			Engine(void);
			Engine(Engine const &src);

			Application		&_app;
			StateMachine	_SM;

			//void	_StartOpenGL();
			//void	_CloseOpenGL();
	};

	std::ostream	&operator<<(std::ostream &o, Engine const &rhs);

#endif
