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
	:GameObject(x, y)
{
}

Enemy::~Enemy()
{
}

void Enemy::update(Level& level)
{
	_movementComponent->update(*this, level);
	_colliderComponent->update(*this, level);
	_physicsComponent->update(*this, level);

}

void Enemy::render(Level& level)
{
	_renderComponent->update(*this, level);
}

bool Enemy::isDead()
{
	return _healthComponent->isDead();
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

void Enemy::setRenderComponent(std::shared_ptr<RenderComponent> renderComponent)
{
	_renderComponent = renderComponent;
	//
	_colliderComponent = std::make_shared<ColliderComponent>(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight());
	_physicsComponent = std::make_shared<PhysicsComponent>();

	addComponent(_renderComponent.get());
	addComponent(_colliderComponent.get());
	addComponent(_physicsComponent.get());
}

void Enemy::setHealthComponent(std::shared_ptr<HealthComponent> healthComponent)
{
	_healthComponent = healthComponent;
	addComponent(_healthComponent.get());
}

void Enemy::setMovementComponent(std::shared_ptr<AIComponent> movementComponent)
{
	_movementComponent = movementComponent;
	addComponent(_movementComponent.get());
}
