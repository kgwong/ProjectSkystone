#include "PlayerProjectile.h"

#include "AnimationRenderer.h"

#include <cmath>
#include "CircleMath.h"
#include "TextureLoader.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "DamageComponent.h"
#include "RenderComponent.h"

PlayerProjectile::PlayerProjectile(Point position, int vel, double degrees)
	:GameObject(position),
	_damageComponent(new DamageComponent(1000)), 
	_physicsComponent(new PhysicsComponent())
{
	_physicsComponent->enableGravity(false);

	int newVelX = (int)(vel * cos(toRadians(degrees)));
	int newVelY = (int)(vel * sin(toRadians(degrees)));
	_physicsComponent->setVelX(newVelX); //
	_physicsComponent->setVelY(newVelY); //

	addComponent(_physicsComponent);
	addComponent(_damageComponent);
}


PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent)
{
	_colliderComponent = colliderComponent;
	addComponent(_colliderComponent);
}

/*void PlayerProjectile::setRenderComponent(std::shared_ptr<RenderComponent> renderComponent)
{
	_renderComponent = renderComponent;
	_colliderComponent = std::make_shared<ColliderComponent>(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight());
	addComponent(_renderComponent);
	addComponent(_colliderComponent);
}*/

void PlayerProjectile::update(Level& level)
{
	_colliderComponent->update(*this, level);
	_physicsComponent->update(*this, level);
}

/*void PlayerProjectile::render(Level& level)
{
	_renderComponent->update(*this, level);
}*/

void PlayerProjectile::onCollision(CollisionInfo& collision)
{
	alive_ = false;
}

EntityType PlayerProjectile::getType() const
{
	return EntityType::PLAYER_PROJECTILE;
}
