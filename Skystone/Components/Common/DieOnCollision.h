#ifndef DIE_ON_COLLISION_H
#define DIE_ON_COLLISION_H

#include "Components/NonUpdatingComponent.h"

class DieOnCollision : public NonUpdatingComponent
{
public:
	DieOnCollision(GameObject& owner);
	virtual ~DieOnCollision();

	virtual void handleEvent(const CollisionEvent& e);
};

#endif //DIE_ON_COLLISION_H