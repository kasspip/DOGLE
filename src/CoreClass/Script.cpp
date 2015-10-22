#include "Script.hpp"
#include "GameObject.hpp"

// CONSTRUCTOR DESTRUCTOR //

Script::Script(std::string n)
{
	name = n;
}

Script::~Script(void)
{

}

Script::Script(Script const &src)
{
	*this = src;
}

// OVERLOADS //

Script& 		Script::operator=(Script const &rhs)
{
	name = rhs.name;
	return *this;
}

// PUBLIC //

std::string		Script::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Script #" << std::endl;
	ss << name << std::endl;
	return ss.str();
}

void			Script::Save(std::ofstream &file)
{
	std::string TABS;
	if (gameObject->IsPrefab() == true)
		TABS = "\t\t";
	else
	 	TABS = "\t\t\t";
	file << TABS <<"SCRIPT:" 
	<< name << std::endl;

}

void			Script::Destroy(GameObject *go)
{
	go->SetDestroy(true);
}

void			Script::Awake() 	{}
void			Script::Update() 	{}
void			Script::OnGUI()		{}
void			Script::OnPause()	{}
void			Script::OnDestroy() {}
void			Script::OnStop() 	{}

// PRIVATE //

// GETTER SETTER //
