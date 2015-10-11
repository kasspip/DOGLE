#include "Start.hpp"

// CONSTRUCTOR DESTRUCTOR //

Start::Start(void)
{
	std::cout << " CONSTRUCT Start " << std::endl;
}

Start::Start(Start const & src)
{
	*this = src;
}

Start::~Start(void)
{

}

// OVERLOADS //

Start	&Start::operator=(Start const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Start const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Start::RunState(Application & app, e_state & currentState)
{
	std::cout << "< State Start >" << std::endl;
	Scene *scene = app.currentScene;
	
	if (scene)
	{
		std::list<GameObject *> GameObjects = scene->GetGameObjectList();
		std::list<GameObject*>::iterator go = GameObjects.begin();
		Skin *skin = NULL;

		for (; go != GameObjects.end(); go++)
		{
			std::cout << (*go)->name << std::endl;
			if ((skin = (*go)->GetComponent<Skin>()))
				_BindBuffers(*skin);
		}
	}
	currentState = EXIT;
}

std::string		Start::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //

void			Start::_BindBuffers(Skin & skin)
{
	std::cout << "-> bind buffers of " << skin.texture_file << std::endl;
}

// GETTER SETTER //
