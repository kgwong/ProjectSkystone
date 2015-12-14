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

	//oid setRenderComponent(std::shared_ptr<RenderComponent> renderComponent);
	void setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent);

	void update(Level& level);
	//void render(Level& level);

	virtual void onCollision(CollisionInfo& collision);
	virtual EntityType getType() const;

private:
	std::shared_ptr<RenderComponent> _renderComponent; 
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;
	std::shared_ptr<DamageComponent> _damageComponent;

};

#endif //PLAYER_PROJECTILE_H