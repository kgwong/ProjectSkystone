#ifndef PICKUP_COMPONENT_H
#define PICKUP_COMPONENT_H

#include "NonUpdatingComponent.h"

class PickupComponent : public NonUpdatingComponent
{
public:
	PickupComponent(GameObject& owner);
	virtual ~PickupComponent();

	virtual void handleEvent(const CollisionEvent& e);
};

#endif //PICKUP_COMPONENT_H