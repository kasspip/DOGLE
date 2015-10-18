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
	return "";
}

void			Script::Save(std::ofstream &file)
{
	file << "ERROR SAVE MOTHER SCRIPT" << std::endl;
}

void			Script::Awake() {}

void			Script::Update() {}



// PRIVATE //

// GETTER SETTER //
