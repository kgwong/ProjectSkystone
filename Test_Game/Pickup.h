#ifndef PICKUP_H
#define PICKUP_H

#include "GameObject.h"
#include "Sprite.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"

class Pickup : public GameObject
{
public:
	Pickup(GameWindow* gw, Sprite* sprite);
	virtual ~Pickup();

	void update(LevelEntities& entities);
	void render();

	bool isDead();

	virtual EntityType getType() const;
	virtual void onCollision(GameObject& other);
	virtual Component* getComponent(ComponentType type);

private:
	bool _alive;

	Sprite* _sprite;
	PhysicsComponent _physicsComponent;
	ColliderComponent _colliderComponent;
};

#endif //PICKUP_H