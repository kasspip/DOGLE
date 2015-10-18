#include "GameObject.hpp"
#include "Transform.hpp"
#include "SCRIPTS.hpp"
#include "IComponent.hpp"

#define FUNC(class)   

size_t GameObject::counter = 0;

// CONSTRUCTOR DESTRUCTOR //

GameObject::GameObject(void) :	_id(counter)
{
	std::stringstream	ss;

	ss << "GameObject " << _id;
	name = ss.str();
	counter++;
	std::cout << "construct GameObject " << std::endl;
	_isPrefab = true; //new

	AddComponent(new Transform());
}

GameObject::GameObject(std::string n) :	_id(counter)
{
	name = n;
	counter++;
	std::cout << "construct GameObject " << name << std::endl;
	_isPrefab = true; //new

	AddComponent(new Transform());
}

GameObject::GameObject(GameObject const & src)
{
	std::cout << "construct copy GameObject " << src.name << std::endl;
	_isPrefab = false; //new
	
	*this = src;
}

GameObject::~GameObject(void)
{
	std::cout << "destruct " + name << std::endl;
	std::list<IComponent*>::iterator it = _listComponent.begin();
	for (; it != _listComponent.end(); it++)
	{
		if (dynamic_cast<Script*>(*it) && !_isPrefab) // new
			continue;
		delete *it;
	}
}

// OVERLOADS //

GameObject&				GameObject::operator=(GameObject const & rhs)
{
	name = rhs.name + " (Copy)";
	std::list<IComponent*> list = rhs.GetListComponent();
	
	std::list<IComponent*>::iterator compo = list.begin();
	for (; compo != list.end(); compo++)
	{
		if (dynamic_cast<Transform*>(*compo))
			AddComponent(new Transform(*(dynamic_cast<Transform*>(*compo))));
		else if (dynamic_cast<Skin*>(*compo))
			AddComponent(new Skin(*(dynamic_cast<Skin*>(*compo))));
		else if (dynamic_cast<Camera*>(*compo))
			AddComponent(new Camera(*(dynamic_cast<Camera*>(*compo))));
		else if (dynamic_cast<Light*>(*compo))
			AddComponent(new Light(*(dynamic_cast<Light*>(*compo))));
		else if (dynamic_cast<Script*>(*compo))
			AddComponent( *compo );
		else
			throw DError() << msg("GameObject operator= overload. Missing component");
	}
	return *this;
}

std::ostream&			operator<<(std::ostream & o, GameObject & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string				GameObject::toString(void)
{
	std::list<IComponent*>::iterator compo = _listComponent.begin();

	std::stringstream ss;
	ss 	<< "<" + name + ">" << std::endl
		<< "id : " << _id	<< std::endl
		<< "Components :"	<< std::endl;
	for (; compo != _listComponent.end(); compo++)
		ss	<< (*compo)->toString() << std::endl;
	;
	return ss.str();
}

void					GameObject::Save(std::ofstream &file)
{
	file << "\t\tGAMEOBJECT : " << name << std::endl;
	std::list<IComponent*>::iterator compo = _listComponent.begin();
	for (;compo != _listComponent.end();compo++)
		(*compo)->Save(file);
}

void					GameObject::AddComponent(IComponent *compo)
{
	compo->gameObject = this;
	if (!dynamic_cast<Transform*>(compo))
		compo->transform = this->GetComponent<Transform>();
	else
	{
		std::cout << "TRANSFORM " <<  std::endl;
		compo->transform = dynamic_cast<Transform*>(compo);
		for (IComponent *i : _listComponent) 
			i->transform = dynamic_cast<Transform*>(compo);
	}
	_listComponent.push_back(compo);
}

// PRIVATE //

// GETTER SETTER //

std::list<IComponent*>	GameObject::GetListComponent() const { return _listComponent;}

