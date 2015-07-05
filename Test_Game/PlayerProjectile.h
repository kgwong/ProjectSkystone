#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "CollidingObject.h"
#include "PhysicalObject.h"

#include "Animation.h"

#include "Direction.h"

class PlayerProjectile : public CollidingObject,
						 public PhysicalObject
{
public:
	PlayerProjectile(Point position, int vel, Animation* animation, Direction dir);
	~PlayerProjectile();

	void update();
	void draw();

private:
	Animation* _animation;

};

#endif //PLAYERPROJECTILE_H