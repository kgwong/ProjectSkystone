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
	_colliderComponent.update(*this);
	_physicsComponent.update(*this, level, &_colliderComponent);
}

void Enemy::render()
{
	_renderComponent->update(*this);
}

void Enemy::takeDamage(int damage)
{
	_healthComponent->takeDamage(damage);
}

bool Enemy::isDead()
{
	return _healthComponent->isDead();
}

void Enemy::onDeath(Level& level)
{
	level.addPickupAtLocation(position);
}

Component* Enemy::getComponent(ComponentType type)
{
	if (type == ComponentType::COLLIDER)
		return &_colliderComponent;
	return nullptr;
}

std::string Enemy::getName()
{
	return "Enemy";
}

EntityType Enemy::getType() const
{
	return EntityType::ENEMY;
}

void Enemy::onCollision(GameObject& other)
{
	if (other.getType() == EntityType::PLAYER_PROJECTILE)
	{
		//well this is ugly
		takeDamage(*((int*)other.getComponent(ComponentType::DAMAGE)->getAttribute("damage")));
	}
}


//private

void Enemy::setRenderComponent(RenderComponent* renderComponent)
{
	_renderComponent = std::shared_ptr<RenderComponent>(renderComponent);
	//
	_colliderComponent = ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight());
}

void Enemy::setHealthComponent(HealthComponent* healthComponent)
{
	_healthComponent = std::shared_ptr<HealthComponent>(healthComponent);
}