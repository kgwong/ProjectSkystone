#ifndef NON_UPDATING_COMPONENT_H
#define NON_UPDATING_COMPONENT_H

#include "Component.h"

class NonUpdatingComponent : public Component
{
public:
	NonUpdatingComponent(GameObject& owner);
	virtual ~NonUpdatingComponent() = 0;

	virtual void update(Level& level) final;

	virtual Component::Type getType() final;
};

#endif //NON_UPDATING COMPONENT_H