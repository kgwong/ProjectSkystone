#ifndef PLAYER_PROJECTILE_H
#define PLAYER_PROJECTILE_H

#include <memory>

#include "Direction.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "DamageComponent.h"
#include "RenderComponent.h"

#include "TextureLoader.h"

class PlayerProjectile : public GameObject
{
public:
	PlayerProjectile(Point position, int vel, TextureLoader* textureLoader, double degrees);
	~PlayerProjectile();

	bool isDead();
	void update(Level& level);
	void render();

	virtual void onCollision(CollisionInfo& collision);
	virtual EntityType getType() const;

private:
	bool _alive;
	std::shared_ptr<RenderComponent> _renderComponent; 
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;
	std::shared_ptr<DamageComponent> _damageComponent;

};

#endif //PLAYER_PROJECTILE_H