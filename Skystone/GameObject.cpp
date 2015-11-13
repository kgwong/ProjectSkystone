#include "GameObject.h"


GameObject::GameObject()
	:width_(0), height_(0)
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

void GameObject::setWidth(int w)
{
	width_ = w;
}

void GameObject::setHeight(int h)
{
	height_ = h;
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

int GameObject::getWidth() const
{
	return width_;
}

int GameObject::getHeight() const
{
	return height_;
}

void GameObject::setCenterPos(const GameObject& other)
{
	position_ = other.getCenterPos();
	position_.x -= width_/2;
	position_.y -= height_/2;
}


void GameObject::setCenterPos(Point newCenterPos)
{
	position_ = newCenterPos;
	position_.x -= width_/2;
	position_.y -= height_/2;
}		

void GameObject::setCenterPosX(int x)
{
	position_.x = x - width_/2;
}

void GameObject::setCenterPosY(int y)
{
	position_.y = y - height_/2;
}

Point GameObject::getCenterPos() const
{
	return Point(position_.x + width_/2, position_.y + height_/2);
}


int GameObject::getCenterPosX() const
{
	return position_.x + width_/2; 
}

int GameObject::getCenterPosY() const
{
	return position_.y + height_/2;
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
