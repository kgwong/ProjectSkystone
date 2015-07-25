#include "Pickup.h"


Pickup::Pickup(GameWindow* gw, Sprite* sprite)
	:_alive(true), _sprite(sprite)
{
	width = _sprite->getWidth();
	height = _sprite->getHeight();
}


Pickup::~Pickup()
{
}

void Pickup::update(LevelEntities& entities)
{
	_colliderComponent.update(*this);
	_physicsComponent.update(*this, entities, &_colliderComponent);
}

void Pickup::render()
{
	_sprite->render(position.x, position.y);
}

bool Pickup::isDead()
{
	return !_alive;
}

EntityType Pickup::getType() const
{
	return PICKUP;
}

void Pickup::onCollision(GameObject& other)
{
	if (other.getType() == PLAYER)
		_alive = false;
}

Component* Pickup::getComponent(ComponentType type)
{
	if (type == COLLIDER)
		return &_colliderComponent;
	return nullptr;
}