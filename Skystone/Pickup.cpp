#include "Pickup.h"

#include "SpriteRenderer.h"

#include "TextureLoader.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"


Pickup::Pickup(Point position)
	:GameObject(position),
	_alive(true),
	_physicsComponent(new PhysicsComponent())
{
	addComponent(_physicsComponent.get());
}

Pickup::~Pickup()
{
}

void Pickup::setRenderComponent(std::shared_ptr<RenderComponent> renderComponent)
{
	_renderComponent = renderComponent;
	_colliderComponent = std::make_shared<ColliderComponent>(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight()),
	addComponent(_renderComponent.get());
	addComponent(_colliderComponent.get());

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