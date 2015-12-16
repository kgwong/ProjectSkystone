#ifndef DIE_ON_COLLISION_H
#define DIE_ON_COLLISION_H

#include "Component.h"

class DieOnCollision : public Component
{
public:
	DieOnCollision(GameObject& owner);
	virtual ~DieOnCollision();

	virtual void handleEvent(const CollisionEvent& e);
};

#endif //DIE_ON_COLLISION_H