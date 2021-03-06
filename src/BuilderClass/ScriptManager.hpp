#ifndef SCRIPTMANAGER_HPP
# define SCRIPTMANAGER_HPP

# include "DOGLE.hpp"
# include <cstdlib>

	class ScriptManager
	{
		public:

			static std::string		pathToRegister;
			static std::string		registerFile;
			static std::string		pathToInclude;
			static std::string		includeFile;
			static std::string		makefileSources;

			ScriptManager(void);
			~ScriptManager(void);

			int						NewScript(std::string name);
			int						EditScriptName(std::string name, std::string newName, std::string dogleFile = "");
			bool					ScriptExists(std::string name);
			void					RemoveScript(std::string name);
			std::list<std::string>	GetScriptsNames();
			std::string				ToString();

		private:
			ScriptManager(ScriptManager const &src);
			ScriptManager &operator=(ScriptManager const &rhs);
	
			int						_PrintError(std::string err);
			void					_FileEraseLine(std::string path, std::string fileName, std::string target);
			void					_SnippetScript(std::ofstream & file, std::string & name);
			void					_FileFindAndReplace(std::string path, std::string fileName, std::string oldName, std::string newName);
			void					_DeleteFile(std::string file);

			std::list<std::string>	_scripts;
	};

#endif
