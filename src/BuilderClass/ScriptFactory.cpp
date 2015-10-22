#include "ScriptFactory.hpp"

std::map<std::string, Script*>ScriptFactory::m_map = std::map<std::string, Script*>();

// CONSTRUCTOR DESTRUCTOR //

ScriptFactory::ScriptFactory(void)
{

}

ScriptFactory::~ScriptFactory(void)
{

}

// OVERLOADS //

// PUBLIC //

void		ScriptFactory::Register(const std::string& key, Script* obj)
{
	if(m_map.find(key)==m_map.end())
		m_map[key]=obj;
}

Script*		ScriptFactory::Create(const std::string& key) const
{
	Script* tmp = nullptr;

	std::map<std::string, Script*>::const_iterator it=m_map.find(key);
	if(it!=m_map.end())
		tmp=((*it).second)->Clone();
	else
		throw DError() << msg("ScriptFactory failed : requested class is not registered.");
	return tmp;
}
// PRIVATE //

// GETTER SETTER //
