#include "GameObject.h"


GameObject::GameObject()
	:width(0), height(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::setPos(int x, int y)
{
	position.x = x;
	position.y = y;
}

void GameObject::setPos(Point newPosition)
{
	position = newPosition;
}

void GameObject::setPosX(int x)
{
	position.x = x;
}

void GameObject::setPosY(int y)
{
	position.y = y;
}

void GameObject::setWidth(int w)
{
	width = w;
}

void GameObject::setHeight(int h)
{
	height = h;
}

Point GameObject::getPos() const
{
	return position;
}

int GameObject::getPosX() const
{
	return position.x;
}

int GameObject::getPosY() const
{
	return position.y;
}

int GameObject::getWidth() const
{
	return width;
}

int GameObject::getHeight() const
{
	return height;
}

void GameObject::setCenterPos(const GameObject& other)
{
	position = other.getCenterPos();
	position.x -= width/2;
	position.y -= height/2;
}


void GameObject::setCenterPos(Point newCenterPos)
{
	position = newCenterPos;
	position.x -= width/2;
	position.y -= height/2;
}		

void GameObject::setCenterPosX(int x)
{
	position.x = x - width/2;
}

void GameObject::setCenterPosY(int y)
{
	position.y = y - height/2;
}

Point GameObject::getCenterPos() const
{
	return Point(position.x + width/2, position.y + height/2);
}


int GameObject::getCenterPosX() const
{
	return position.x + width/2; 
}

int GameObject::getCenterPosY() const
{
	return position.y + height/2;
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