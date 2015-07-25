#include "Enemy.h"


Enemy::Enemy(GameWindow* gw, Sprite* sprite)
	: _sprite(sprite), _healthComponent(100)
{
	width = _sprite->getWidth();
	height = _sprite->getHeight();
}


Enemy::~Enemy()
{
}

void Enemy::update(LevelEntities& entities)
{
	_colliderComponent.update(*this);
	_physicsComponent.update(*this, entities, &_colliderComponent);
}

void Enemy::render()
{
	_sprite->render(position.x, position.y);
}

void Enemy::takeDamage(int damage)
{
	_healthComponent.takeDamage(damage);
}

bool Enemy::isDead()
{
	return _healthComponent.isDead();
}

std::string Enemy::getName()
{
	return "Enemy";
}

EntityType Enemy::getType() const
{
	return ENEMY;
}

void Enemy::onCollision(GameObject& other)
{
	if (other.getType() == PLAYER_PROJECTILE)
	{
		//well this is ugly
		takeDamage(*((int*)other.getComponent(DAMAGE)->getAttribute("damage"))); 
	}
}