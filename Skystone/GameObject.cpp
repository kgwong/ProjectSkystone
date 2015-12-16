#include "GameObject.h"

#include "Component.h" //for CallStartOnComponents... 
#include "ComponentSystem.h"

GameObject::GameObject()
	:alive_(true), 
	type_(GameObject::Type::UNKNOWN)
{
}

GameObject::GameObject(Point position)
	: position_(position), 
	alive_(true), 
	type_(GameObject::Type::UNKNOWN)
{
}

GameObject::GameObject(int x, int y)
	:position_(Point(x, y)), 
	alive_(true), 
	type_(GameObject::Type::UNKNOWN)
{
}

GameObject::~GameObject()
{
}

void GameObject::setPos(int x, int y)
{
	position_.x = x;
	position_.y = y;
}

void GameObject::setPos(Point newPosition)
{
	position_ = newPosition;
}

void GameObject::setPosX(int x)
{
	position_.x = x;
}

void GameObject::setPosY(int y)
{
	position_.y = y;
}

Point GameObject::getPos() const
{
	return position_;
}

int GameObject::getPosX() const
{
	return position_.x;
}

int GameObject::getPosY() const
{
	return position_.y;
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
	if (component)
		components_[&typeid(*component)] = component;
}

void GameObject::disownComponents()
{
	for (auto& c : components_)
	{
		c.second->disown();
	}
}

void GameObject::registerComponents(ComponentSystem& system)
{
	for (auto& c : components_)
	{
		system.addComponent(c.second);
	}
}

bool GameObject::alive()
{
	return alive_;
}

void GameObject::kill()
{
	alive_ = false;
	this->disownComponents();
}

void GameObject::setType(GameObject::Type type)
{
	type_ = type;
}

GameObject::Type GameObject::getType() const
{
	return type_;
}

void GameObject::startComponents(Level& level)
{
	for (auto& i : components_)
	{
		i.second->start(level);
	}
}

void GameObject::broadcastEvent(const ComponentEvent& e)
{
	for (auto& c : components_)
	{
		c.second->handleEvent(e);
	}
}

void GameObject::broadcastEvent(const CollisionEvent & e)
{
	for (auto& c : components_)
	{
		c.second->handleEvent(e);
	}
}
