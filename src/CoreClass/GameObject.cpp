#include "GameObject.hpp"
#include "Transform.hpp"
#include "SCRIPTS.hpp"
#include "IComponent.hpp"

#define FUNC(class)   

size_t GameObject::counter = 0;

// CONSTRUCTOR DESTRUCTOR /

GameObject::GameObject(std::string n) :	_id(counter)
{
	name = n;
	_id = counter++;
	std::cout << "construct GameObject " << name << std::endl;
	_isPrefab = true;
	_destroyMe = false;
	AddComponent(new Transform());
}

GameObject::GameObject(GameObject const & src)
{
	_id = counter++;
	_isPrefab = false;
	*this = src;
	std::cout << "construct GameObject " << name << " from " << src.name << std::endl;
}

GameObject::~GameObject(void)
{
	std::cout << "destruct " + name << std::endl;
	for (IComponent* compo : _listComponent)
		delete compo;
}

// OVERLOADS //

GameObject&				GameObject::operator=(GameObject const & rhs)
{
	std::stringstream ss;
	ss << rhs.name + " (" << _id << ")";
	name = ss.str();
	for (IComponent* compo : rhs.GetListComponent())
	{
		if (dynamic_cast<Transform*>(compo))
			AddComponent(new Transform(*(dynamic_cast<Transform*>(compo))));
		else if (dynamic_cast<Skin*>(compo))
			AddComponent(new Skin(*(dynamic_cast<Skin*>(compo))));
		else if (dynamic_cast<Camera*>(compo))
			AddComponent(new Camera(*(dynamic_cast<Camera*>(compo))));
		else if (dynamic_cast<Light*>(compo))
			AddComponent(new Light(*(dynamic_cast<Light*>(compo))));
		else if (dynamic_cast<Script*>(compo))
			AddComponent(dynamic_cast<Script*>(compo)->Clone());
		else
			throw DError() << msg("GameObject operator= overload. Missing component");
	}
	_destroyMe = rhs._destroyMe;
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
	std::stringstream ss;
	ss 	<< "<" + name + ">" << std::endl
		<< "id : " << _id	<< std::endl
		<< "Components :"	<< std::endl;
	for (IComponent* compo : _listComponent)
		ss	<< compo->toString() << std::endl;
	return ss.str();
}

void					GameObject::Save(std::ofstream &file)
{
	std::string TABS;
	std::string TYPE;
	if (_isPrefab == true)
	{
		TABS = "\t";
		TYPE = "PREFAB";
	}
	else
	{
		TABS = "\t\t";
		TYPE = "GAMEOBJECT";
	}
	file << TABS << TYPE << " : " << name << std::endl;
	for (IComponent* compo : _listComponent)
		compo->Save(file);
}

void					GameObject::AddComponent(IComponent *compo)
{
	compo->gameObject = this;
	if (!dynamic_cast<Transform*>(compo))
		compo->transform = this->GetComponent<Transform>();
	else
	{
		compo->transform = dynamic_cast<Transform*>(compo);
		for (IComponent *i : _listComponent) 
			i->transform = dynamic_cast<Transform*>(compo);
	}
	_listComponent.push_back(compo);
}

// PRIVATE //

std::string				GameObject::_GetDefaultName()
{
	std::stringstream	ss;

	ss << "GameObject " << counter;
	return (ss.str());
}


// GETTER SETTER //

std::list<IComponent*>	GameObject::GetListComponent() const { return _listComponent;}
void					GameObject::SetDestroy(bool set) { _destroyMe = set; }
bool					GameObject::GetDestroy() { return _destroyMe; }
bool					GameObject::IsPrefab() { return _isPrefab; }

