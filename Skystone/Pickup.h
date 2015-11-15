#ifndef PICKUP_H
#define PICKUP_H

#include <memory>

#include "GameObject.h"

class TextureLoader;
class RenderComponent;
class PhysicsComponent;
class ColliderComponent;

class Pickup : public GameObject
{
public:
	Pickup(TextureLoader* textureLoader);
	virtual ~Pickup();

	void update(Level& level);
	void render(Level& level);

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