#ifndef PLAYER_PROJECTILE_H
#define PLAYER_PROJECTILE_H

#include <memory>

#include "Animation.h"
#include "Direction.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "DamageComponent.h"
#include "RenderComponent.h"

class PlayerProjectile : public GameObject
{
public:
	PlayerProjectile(Point position, int vel, Animation* animation, Direction dir);
	~PlayerProjectile();

	bool isDead();
	void update(Level& level);
	void render();

	Component* getComponent(ComponentType type);

	virtual void onCollision(GameObject& other);
	virtual EntityType getType() const;

private:
	bool _alive;
	Animation* _animation;
	std::shared_ptr<RenderComponent> _renderComponent; //lazy!!
	PhysicsComponent _physicsComponent;
	ColliderComponent _colliderComponent;
	DamageComponent _damageComponent;

};

#endif //PLAYER_PROJECTILE_H