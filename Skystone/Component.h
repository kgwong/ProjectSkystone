#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include "Level.h"

#include "ComponentEvent.h"
#include "CollisionEvent.h"

class Component
{
public:
	Component(GameObject& owner);
	virtual ~Component() = 0;

	virtual void start(Level& level);
	virtual void update(Level& level);

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const ComponentEvent& e);

	bool owned();
	void disown();

protected:
	GameObject& owner_;
	bool owned_;
};

#endif //COMPONENT_H