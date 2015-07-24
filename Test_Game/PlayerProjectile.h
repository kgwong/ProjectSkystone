#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "Animation.h"
#include "Direction.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "DamageComponent.h"

struct LevelEntities;

class PlayerProjectile : public GameObject
{
public:
	PlayerProjectile(Point position, int vel, Animation* animation, Direction dir);
	~PlayerProjectile();

	bool isDead();
	void update(LevelEntities& entities);
	void render();

	Component* getComponent(ComponentType type);

	virtual void onCollision(GameObject& other);
	virtual EntityType getType() const;

private:
	bool _alive;
	Animation* _animation;
	PhysicsComponent _physicsComponent;
	ColliderComponent _colliderComponent;
	DamageComponent _damageComponent;

};

#endif //PLAYERPROJECTILE_H