#include "GameObject.h"

#include "Component.h" //for CallStartOnComponents... 

GameObject::GameObject()
{
}

GameObject::GameObject(Point position)
	:position_(position)
{
}

GameObject::GameObject(int x, int y)
	:position_(Point(x, y))
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

void GameObject::addComponent(Component* component)
{
	if (component)
		components_[&typeid(*component)] = component;
}

std::string GameObject::getName() const
{
	return ""; //intended to be overridden
}

EntityType GameObject::getType() const
{
	return EntityType::NONE;
}

void GameObject::callStartOnComponents(Level& level)
{
	for (auto& i : components_)
	{
		i.second->start(*this, level);
	}
}
