#ifndef UPDATING_COMPONENT_H
#define UPDATING_COMPONENT_H

#include "Component.h"
#include "CollisionEvent.h"

class UpdatingComponent : public Component
{
public:
	UpdatingComponent(GameObject& owner);
	virtual ~UpdatingComponent() = 0;

	virtual void update(Level& level) = 0;
	virtual void handleEvent(const CollisionEvent& other);

	virtual Component::Type getType();
};

#endif //UPDATING_COMPONENT_H