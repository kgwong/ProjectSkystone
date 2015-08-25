#ifndef PICKUP_H
#define PICKUP_H

#include <memory>

#include "GameObject.h"
#include "ResourceLocator.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"

class Pickup : public GameObject
{
public:
	Pickup(ResourceLocator* resourceLocator);
	virtual ~Pickup();

	void update(Level& level);
	void render();

	bool isDead();

	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision);

private:
	bool _alive;

	std::shared_ptr<RenderComponent> _renderComponent;
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;
};

#endif //PICKUP_H