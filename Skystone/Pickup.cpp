#include "Pickup.h"

#include "SpriteRenderer.h"

#include "TextureLoader.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"

Pickup::Pickup()
{

}

Pickup::Pickup(Point position)
	:GameObject(position),
	_physicsComponent(new PhysicsComponent(*this))
{
	addComponent(_physicsComponent);
}

Pickup::~Pickup()
{
}

void Pickup::update(Level& level)
{
	_physicsComponent->update(level);
}

void Pickup::setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent)
{
	_colliderComponent = colliderComponent;
	addComponent(_colliderComponent);
}

EntityType Pickup::getType() const
{
	return EntityType::PICKUP;
}

void Pickup::onCollision(CollisionInfo& collision)
{
	if (collision.other.getType() == EntityType::PLAYER)
		alive_ = false;
}