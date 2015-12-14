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
	_damageComponent(new DamageComponent(*this, 1000)), 
	_physicsComponent(new PhysicsComponent(*this))
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

void PlayerProjectile::update(Level& level)
{
	_colliderComponent->update(level);
	_physicsComponent->update(level);
}

void PlayerProjectile::onCollision(CollisionInfo& collision)
{
	alive_ = false;
}

EntityType PlayerProjectile::getType() const
{
	return EntityType::PLAYER_PROJECTILE;
}
