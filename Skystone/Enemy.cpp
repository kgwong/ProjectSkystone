#include "Enemy.h"

#include "Level.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "AIComponent.h"
#include "DamageComponent.h"


Enemy::Enemy()
{
}

Enemy::Enemy(Point position)
	:GameObject(position)
{
}

Enemy::Enemy(int x, int y)
	: GameObject(x, y)
{
}

Enemy::~Enemy()
{
}

void Enemy::update(Level& level)
{
}

void Enemy::onDeath(Level& level)
{
	level.addPickupAtLocation(position_);
}

void Enemy::onCollision(CollisionInfo& collision)
{
	if (collision.other.getType() == ObjectType::PLAYER_PROJECTILE)
	{
		getComponent<HealthComponent>()->takeDamage(collision.other.getComponent<DamageComponent>()->getDamage());
	}
}