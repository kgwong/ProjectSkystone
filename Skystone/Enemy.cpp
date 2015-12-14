#include "Enemy.h"

#include "Level.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "AIComponent.h"
#include "DamageComponent.h"

#include <iostream> //

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
	_healthComponent->update(*this, level);
	_movementComponent->update(*this, level);
	_colliderComponent->update(*this, level);
	_physicsComponent->update(*this, level);

}

void Enemy::onDeath(Level& level)
{
	level.addPickupAtLocation(position_);
}

std::string Enemy::getName()
{
	return "Enemy";
}

EntityType Enemy::getType() const
{
	return EntityType::ENEMY;
}

void Enemy::onCollision(CollisionInfo& collision)
{
	if (collision.other.getType() == EntityType::PLAYER_PROJECTILE)
	{
		_healthComponent->takeDamage(collision.other.getComponent<DamageComponent>()->getDamage());
	}
}

void Enemy::setColliderComponent(std::shared_ptr<ColliderComponent> component)
{
	_colliderComponent = component;
	addComponent(_colliderComponent);
}

void Enemy::setHealthComponent(std::shared_ptr<HealthComponent> healthComponent)
{
	_healthComponent = healthComponent;
	addComponent(_healthComponent);
}

void Enemy::setMovementComponent(std::shared_ptr<AIComponent> movementComponent)
{
	_movementComponent = movementComponent;
	addComponent(_movementComponent);
	_physicsComponent = std::make_shared<PhysicsComponent>();
	damageComponent_ = std::make_shared<DamageComponent>(10);
	addComponent(_physicsComponent);
	addComponent(damageComponent_);
}
