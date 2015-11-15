#include "PlayerProjectile.h"

#include "AnimationRenderer.h"

#include <cmath>
#include "CircleMath.h"
#include "TextureLoader.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "DamageComponent.h"
#include "RenderComponent.h"

PlayerProjectile::PlayerProjectile(Point position, int vel, TextureLoader* textureLoader, double degrees)
	:GameObject(position),
	_alive(true), 
	_damageComponent(new DamageComponent(10)), 
	_renderComponent(new AnimationRenderer(textureLoader->getTextureSheet("Assets/Animations/playerProjectile.png"))),
	_colliderComponent(new ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())),
	_physicsComponent(new PhysicsComponent())
{
	_physicsComponent->enableGravity(false);

	int newVelX = (int)(vel * cos(toRadians(degrees)));
	int newVelY = (int)(vel * sin(toRadians(degrees)));
	_physicsComponent->setVelX(newVelX); //
	_physicsComponent->setVelY(newVelY); //

	addComponent(_renderComponent.get());
	addComponent(_physicsComponent.get());
	addComponent(_colliderComponent.get());
	addComponent(_damageComponent.get());
	//callStartOnComponents();
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
	_colliderComponent->update(*this, level);
	_physicsComponent->update(*this, level);
}

void PlayerProjectile::render(Level& level)
{
	_renderComponent->update(*this, level);
}

void PlayerProjectile::onCollision(CollisionInfo& collision)
{
	_alive = false;
}

EntityType PlayerProjectile::getType() const
{
	return EntityType::PLAYER_PROJECTILE;
}
