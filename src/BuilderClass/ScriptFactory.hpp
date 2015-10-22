#ifndef SCRIPTFACTORY_HPP
# define SCRIPTFACTORY_HPP

# include "DOGLE.hpp"
# include "Script.hpp"
# include <map>

	class ScriptFactory
	{
		public:
			ScriptFactory(void);
			~ScriptFactory(void);
		
			static std::map<std::string,Script*> m_map;

        	Script* Create(const std::string& key) const;
			static void Register(const std::string& key, Script* obj);

		private:
			ScriptFactory(ScriptFactory const &src);
			ScriptFactory &operator=(ScriptFactory const &rhs);
	};

#endif
