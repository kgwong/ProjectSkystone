#ifndef STICK_ON_COLLISION_H
#define STICK_ON_COLLISION_H
#include "Components\NonUpdatingComponent.h"
class StickOnCollision : public NonUpdatingComponent
{
public:
	StickOnCollision(GameObject& owner);
	virtual ~StickOnCollision();

	virtual void handleEvent(const CollisionEvent& e);
	bool isConnected;
};

#endif

