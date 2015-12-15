#ifndef PLAYER_PROJECTILE_H
#define PLAYER_PROJECTILE_H

#include <memory>

#include "GameObject.h"
#include "Direction.h"

class TextureLoader;
class RenderComponent;
class PhysicsComponent;
class ColliderComponent;
class DamageComponent;

class PlayerProjectile : public GameObject
{
public:
	PlayerProjectile(Point position, int vel, double degrees);
	~PlayerProjectile();

	void update(Level& level);

	virtual void onCollision(CollisionInfo& collision);
	virtual ObjectType getType() const;

private:
	std::shared_ptr<DamageComponent> _damageComponent;

};

#endif //PLAYER_PROJECTILE_H