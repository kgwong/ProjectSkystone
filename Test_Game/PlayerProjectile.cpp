#include "PlayerProjectile.h"

#include "AnimationRenderer.h"
//#include "TextureLoader.h"

PlayerProjectile::PlayerProjectile(Point position, int vel, TextureLoader* textureLoader, Direction dir)
	:_alive(true), 
	_damageComponent(new DamageComponent(10)), 
	_renderComponent(new AnimationRenderer(textureLoader->getTextureSheet("Assets/Animations/playerProjectile.png"))),
	_colliderComponent(new ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())),
	_physicsComponent(new PhysicsComponent())
{
	_physicsComponent->enableGravity(false);

	this->position = position; 

	switch (dir)
	{
		case Direction::UP: _physicsComponent->setVelY(-vel); break;
		case Direction::DOWN: _physicsComponent->setVelY(vel); break;
		case Direction::LEFT: _physicsComponent->setVelX(-vel); break;
		case Direction::RIGHT: _physicsComponent->setVelX(vel); break;
		default: break;
	}

	addComponent(_renderComponent.get());
	addComponent(_physicsComponent.get());
	addComponent(_colliderComponent.get());
	addComponent(_damageComponent.get());
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
	_colliderComponent->update(*this);
	_physicsComponent->update(*this, level, _colliderComponent.get());
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
