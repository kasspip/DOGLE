#include "GameObject.hpp"
#include "Transform.hpp"

size_t GameObject::counter = 0;

// CONSTRUCTOR DESTRUCTOR //

GameObject::GameObject(void) :	_id(counter)
{
	std::stringstream	ss;

	ss << "GameObject " << _id;
	name = ss.str();
	counter++;
	std::cout << "construct GameObject" << std::endl;
	AddComponent(new Transform);
}

GameObject::GameObject(std::string n) :	_id(counter)
{
	name = n;
	counter++;
	std::cout << "construct "<< name << std::endl;
	AddComponent(new Transform);
}

GameObject::GameObject(GameObject const & src)
{
	*this = src;
	std::cout << "construct " << name << std::endl;
}

GameObject::~GameObject(void)
{
	std::cout << "destruct " + name << std::endl;
	std::list<IComponent*>::iterator it = _listComponent.begin();
	for (; it != _listComponent.end(); it++)
		delete *it;
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

void					GameObject::AddComponent(IComponent *compt)
{
	_listComponent.push_back(compt);
}

// PRIVATE //

// GETTER SETTER //

std::list<IComponent*>	GameObject::GetListComponent() const { return _listComponent;}

