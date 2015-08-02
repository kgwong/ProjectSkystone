#include "PlayerProjectile.h"


PlayerProjectile::PlayerProjectile(Point position, int vel, Animation* animation, Direction dir)
	:_alive(true), _animation(animation), _damageComponent(10), _renderComponent(_animation)
{
	_physicsComponent.enableGravity(false);

	width = _animation->getWidth();
	height = _animation->getHeight();

	this->position = position; 

	switch (dir)
	{
		case UP: _physicsComponent.setVelY(-vel); break;
		case DOWN: _physicsComponent.setVelY(vel); break;
		case LEFT: _physicsComponent.setVelX(-vel); break;
		case RIGHT: _physicsComponent.setVelX(vel); break;
		default: break;
	}
}


PlayerProjectile::~PlayerProjectile()
{
}

bool PlayerProjectile::isDead()
{
	return !_alive;
}

void PlayerProjectile::update(Level& level)
{
	//if (_alive)
//	{
		_colliderComponent.update(*this);
		_physicsComponent.update(*this, level, &_colliderComponent);
	//}
}

void PlayerProjectile::render()
{
	_renderComponent.update(*this);
}

void PlayerProjectile::onCollision(GameObject& other)
{
	_alive = false;
}

EntityType PlayerProjectile::getType() const
{
	return PLAYER_PROJECTILE;
}

Component* PlayerProjectile::getComponent(ComponentType type) 
{
	if (type == DAMAGE)
	{
		return &_damageComponent;
	}
	return nullptr;
}