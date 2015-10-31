#include "ScriptManager.hpp"

std::string		ScriptManager::pathToRegister = "src/BuilderClass/";
std::string		ScriptManager::pathToInclude = "resources/Scripts/";
std::string		ScriptManager::registerFile = "ScriptsRegister.cpp";
std::string		ScriptManager::includeFile = "SCRIPTS.hpp";
std::string		ScriptManager::makefileSources = "makefile_sources";

// CONSTRUCTOR DESTRUCTOR //

ScriptManager::ScriptManager(void)
{
	std::ifstream 	file(pathToRegister + registerFile);
	std::string		line;

	if (!file.is_open())
		throw DError() << msg("Script manager: Constructor : could not open " + pathToRegister + registerFile);

	while ( getline(file, line) )
	{
		if (line.find("ScriptFactory::Register") != std::string::npos)
		{
			std::size_t start = line.find("\"") + 1; 
			_scripts.push_back(line.substr(start, line.find_last_of("\"") - start));
		}
	}
}

ScriptManager::~ScriptManager(void)
{
	std::list<std::string>::iterator name = _scripts.begin();
	for (; name != _scripts.end(); name++)
		name = _scripts.erase(name);
}

// PUBLIC //

int				ScriptManager::NewScript(std::string name)
{

	if (std::find(_scripts.begin(), _scripts.end(), name) != _scripts.end())
		return (_PrintError("NewScript: script \"" + name + "\" already exists."));
	
	std::ofstream Omakefile(pathToInclude + makefileSources, std::ios_base::app);
	std::ofstream OregisterFile(pathToRegister + registerFile, std::ios_base::app);
	std::ofstream OincludeFile(pathToInclude + includeFile, std::ios_base::app);

	if (!Omakefile.is_open())
		throw DError() << msg("Script manager: NewScript : could not open " + pathToInclude + makefileSources);
 	if (!OregisterFile.is_open())
		throw DError() << msg("Script manager: NewScript : could not open " + pathToRegister + registerFile);
 	if (!OincludeFile.is_open())
		throw DError() << msg("Script manager: NewScript : could not open " + pathToInclude + includeFile);
	
	std::ofstream Ocppfile(pathToInclude + name + ".cpp");
	
	if (!Ocppfile.is_open())
		throw DError() << msg("Script manager: NewScript : could not open " + pathToInclude + name + ".cpp");	

	_SnippetScript(Ocppfile, name);
	Omakefile << "\t\t" << name << ".cpp\\" << std::endl;
	OregisterFile << "ScriptFactory::Register(\"" + name + "\", new " + name + ");" << std::endl;
	OincludeFile << "#include \"" + name + ".cpp\"" << std::endl;

	Ocppfile.close();
	Omakefile.close();
	OregisterFile.close();
	OincludeFile.close();

	_scripts.push_back(name);
	return (1);
}

void			ScriptManager::RemoveScript(std::string name)
{
	if (std::find(_scripts.begin(), _scripts.end(), name) == _scripts.end())
		_PrintError("RemoveScript : script \"" + name + "\" may not exists.");
	std::ofstream Ocppfile(pathToInclude + name + ".cpp");
	if (Ocppfile.is_open())
	{
		Ocppfile.close();
		std::remove((pathToInclude + name + ".cpp").c_str());
	}
	_FileEraseLine(pathToInclude, includeFile, "#include \"" + name + ".cpp\"");
	_FileEraseLine(pathToInclude, makefileSources, "\t\t" + name + ".cpp\\");
	_FileEraseLine(pathToRegister, registerFile, "ScriptFactory::Register(\"" + name + "\", new " + name + ");");
}

std::string		ScriptManager::ToString()
{
	std::stringstream ss;
	ss << "Script's name list :" << std::endl;
	for (std::string name : _scripts)
		ss << name << std::endl;
	return ss.str();
}

// PRIVATE //

int				ScriptManager::_PrintError(std::string err)
{
	std::cout << C_YELLOW << "ScriptManager warning: " << err << C_DEFAULT << std::endl;
	return -1;
}

void			ScriptManager::_FileEraseLine(std::string path, std::string fileName, std::string target)
{
	std::ifstream file(path + fileName);
	std::ofstream newFile(path + "RewriteTmpFile.txt");

	if (!file.is_open())
		throw DError() << msg("Script manager: _FileEraseLine : could not open " + path + fileName);
	if (!newFile.is_open())
		throw DError() << msg("Script manager: _FileEraseLine : could not open " + path + "RewriteTmpFile.txt");
	
	std::string line;
	while ( getline(file, line) )
	{
		if (line != target)
			newFile << line << std::endl;
	}
	file.close();
	std::remove((path + fileName).c_str());
	std::rename((path + "RewriteTmpFile.txt").c_str(), (path + fileName).c_str());
    newFile.close();
}

void			ScriptManager::_SnippetScript(std::ofstream & file, std::string & name)
{
	file
	 << "# include \"DOGLE.hpp\"" << std::endl
	 << "# include \"Script.hpp\"" << std::endl << std::endl

	 << "class " << name << " : public Script" << std::endl 
	 << "{" << std::endl 
	 << 	"\tpublic:" << std::endl << std::endl

	 << 		"\t" << name << "() : Script(\"" << name << "\") {}" << std::endl
	 << 		"\tScript* Clone() { return new "<< name <<"(*this); }" << std::endl << std::endl


	 << "};" << std::endl;
}

// GETTER SETTER //
			
std::list<std::string>	ScriptManager::GetScriptsNames() { return _scripts; }