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

	virtual void onCollision(CollisionInfo& collision);
};

#endif //PICKUP_H