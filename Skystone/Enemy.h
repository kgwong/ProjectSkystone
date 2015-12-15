#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include "GameObject.h"

class Level;
class PhysicsComponent;
class HealthComponent;
class ColliderComponent;
class RenderComponent;
class AIComponent;
class DamageComponent;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Point position);
	Enemy(int x, int y);
	virtual ~Enemy();

	void update(Level& level);

	virtual void onCollision(CollisionInfo& collision);
	virtual void onDeath(Level& level);
};

#endif //ENEMY_H

