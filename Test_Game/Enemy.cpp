#include "Enemy.h"

#include "Level.h"
#include "Pickup.h"

#include "StaticSpriteRenderer.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::update(Level& level)
{
	_colliderComponent->update(*this);
	_physicsComponent->update(*this, level, _colliderComponent.get());
}

void Enemy::render()
{
	_renderComponent->update(*this);
}

bool Enemy::isDead()
{
	return _healthComponent->isDead();
}

void Enemy::onDeath(Level& level)
{
	level.addPickupAtLocation(position);
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


//private

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