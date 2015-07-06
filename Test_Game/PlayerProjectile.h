#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "CollidingObject.h"
#include "PhysicalObject.h"

#include "Animation.h"
#include "Direction.h"

#include "LevelEntities.h"

struct LevelEntities;

class PlayerProjectile : public CollidingObject,
						 public PhysicalObject
{
public:
	PlayerProjectile(Point position, int vel, Animation* animation, Direction dir);
	~PlayerProjectile();

	bool isActive();
	void update(LevelEntities& entities);
	void render();

private:
	bool _active;
	Animation* _animation;

private:
	void handleCollisionX(CollidingObject& other);
	void handleCollisionY(CollidingObject& other);

};

#endif //PLAYERPROJECTILE_H