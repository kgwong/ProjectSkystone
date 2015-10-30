#include "Pickup.h"

#include "SpriteRenderer.h"

Pickup::Pickup(TextureLoader* textureLoader)
	:_alive(true), 
	_renderComponent(new SpriteRenderer(textureLoader->getTextureSheet("Assets/Pickups/pickup.png"))),
	_colliderComponent(new ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())),
	_physicsComponent(new PhysicsComponent())
{
	addComponent(_renderComponent.get());
	addComponent(_physicsComponent.get());
	addComponent(_colliderComponent.get());
	//callStartOnComponents();
}

Pickup::~Pickup()
{
}

void Pickup::update(Level& level)
{
	_colliderComponent->update(*this, level);
	_physicsComponent->update(*this, level);
}

void Pickup::render(Level& level)
{
	_renderComponent->update(*this, level);
}

bool Pickup::isDead()
{
	return !_alive;
}

EntityType Pickup::getType() const
{
	return EntityType::PICKUP;
}

void Pickup::onCollision(CollisionInfo& collision)
{
	if (collision.other.getType() == EntityType::PLAYER)
		_alive = false;
}