#include "GameObject.h"

#include "Components/Component.h" //for CallStartOnComponents... 

GameObject::GameObject()
	: GameObject(Point(0, 0))
{
}

GameObject::GameObject(Point position)
	: position_(position), 
	alive_(true), 
	type_(GameObject::Type::UNKNOWN)
{
}

GameObject::GameObject(int x, int y)
	:GameObject(Point(x, y)) 
{
}

GameObject::~GameObject()
{
}

void GameObject::setPos(float x, float y)
{
	position_.x = x;
	position_.y = y;
}

void GameObject::setPos(Point newPosition)
{
	position_ = newPosition;
}

void GameObject::setPosX(float x)
{
	position_.x = x;
}

void GameObject::setPosY(float y)
{
	position_.y = y;
}

Point GameObject::getPos() const
{
	return position_;
}

float GameObject::getPosX() const
{
	return position_.x;
}

float GameObject::getPosY() const
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
		c.second->setOwned(false);
	}
}

void GameObject::registerComponents(ComponentSystem& system)
{
	for (auto& c : components_)
	{
		system.addComponent(c.second);
		c.second->setOwned(true);
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

void GameObject::setAlive(bool alive)
{
	alive_ = alive;
}

void GameObject::setType(GameObject::Type type)
{
	type_ = type;
}

GameObject::Type GameObject::getType() const
{
	return type_;
}

void GameObject::startComponents(Scene& scene)
{
	for (auto& i : components_)
	{
		i.second->start(scene);
	}
}

void GameObject::broadcastEvent(const ComponentEvent& e)
{
	for (auto& c : components_)
	{
		e.dispatch(*c.second);
	}
}