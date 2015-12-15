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
	:GameObject(position)
{
}


PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::update(Level& level)
{
}

void PlayerProjectile::onCollision(CollisionInfo& collision)
{
	alive_ = false;
}

ObjectType PlayerProjectile::getType() const
{
	return ObjectType::PLAYER_PROJECTILE;
}
