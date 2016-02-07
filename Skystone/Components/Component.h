#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject/GameObject.h"
#include "Level/Level.h"

#include "Events/ComponentEvent.h"
#include "Events/CollisionEvent.h"

class Component
{
public:
	enum class Type {
		UPDATING,
		NON_UPDATING,
		INPUT,
		AI,
		PHYSICS,
		RENDER,
		UNKNOWN
	};

public:
	Component(GameObject& owner);
	virtual ~Component() = 0;

	virtual void start(Level& level);
	virtual void update(Level& level);

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const ComponentEvent& e);

	virtual Type getType();

	bool owned();
	void setOwned(bool owned);

protected:
	GameObject& owner_;
	bool owned_;
};

#endif //COMPONENT_H