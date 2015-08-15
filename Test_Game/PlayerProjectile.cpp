#include "PlayerProjectile.h"

#include "AnimationRenderer.h"

PlayerProjectile::PlayerProjectile(Point position, int vel, Animation* animation, Direction dir)
	:_alive(true), 
	_animation(animation), //
	_damageComponent(10), 
	_renderComponent(new AnimationRenderer(_animation)),
	_colliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())
{
	_physicsComponent.enableGravity(false);

	this->position = position; 

	switch (dir)
	{
		case Direction::UP: _physicsComponent.setVelY(-vel); break;
		case Direction::DOWN: _physicsComponent.setVelY(vel); break;
		case Direction::LEFT: _physicsComponent.setVelX(-vel); break;
		case Direction::RIGHT: _physicsComponent.setVelX(vel); break;
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
	_renderComponent->update(*this);
}

void PlayerProjectile::onCollision(CollisionInfo& collision)
{
	_alive = false;
}

EntityType PlayerProjectile::getType() const
{
	return EntityType::PLAYER_PROJECTILE;
}

Component* PlayerProjectile::getComponent(ComponentType type) 
{
	if (type == ComponentType::DAMAGE)
	{
		return &_damageComponent;
	}
	return nullptr;
}