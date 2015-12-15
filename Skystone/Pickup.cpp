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
	:GameObject(position)
{
}

Pickup::~Pickup()
{
}

void Pickup::onCollision(CollisionInfo& collision)
{
	if (collision.other.getType() == ObjectType::PLAYER)
		alive_ = false;
}