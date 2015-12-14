#ifndef PICKUP_H
#define PICKUP_H

#include <memory>

#include "GameObject.h"

class RenderComponent;
class PhysicsComponent;
class ColliderComponent;

class Pickup : public GameObject
{
public:
	Pickup();
	Pickup(Point position);
	virtual ~Pickup();

	void update(Level& level);

	void setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent);

	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision);

private:
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;
};

#endif //PICKUP_H