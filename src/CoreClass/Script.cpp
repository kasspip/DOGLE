#include "Script.hpp"

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
	(void)rhs;
	return *this;
}

// PUBLIC //

std::string		Script::toString(void) const
{
	std::stringstream ss;
	ss << "# Component Camera #" << std::endl;
	ss << name << std::endl;
	return ss.str();
}

void			Script::Save(std::ofstream &file)
{
	file <<"\t\t\tSCRIPT : " << name << std::endl;
}

void			Script::Destroy(GameObject *go)
{
	go->SetDestroy(true);
}

void			Script::Awake() 	{}
void			Script::Update() 	{}
void			Script::OnPause()	{}
void			Script::OnDestroy() {}
void			Script::OnStop() 	{}

// PRIVATE //

// GETTER SETTER //
