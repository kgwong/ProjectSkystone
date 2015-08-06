#ifndef PICKUP_H
#define PICKUP_H

#include <memory>

#include "GameObject.h"
#include "Sprite.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"

class Pickup : public GameObject
{
public:
	Pickup(Sprite* sprite);
	virtual ~Pickup();

	void update(Level& level);
	void render();

	bool isDead();

	virtual EntityType getType() const;
	virtual void onCollision(GameObject& other);
	virtual Component* getComponent(ComponentType type);

private:
	bool _alive;

	std::shared_ptr<RenderComponent> _renderComponent;
	PhysicsComponent _physicsComponent;
	ColliderComponent _colliderComponent;
};

#endif //PICKUP_H