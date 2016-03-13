#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject/GameObject.h"
#include "Scene/Scene.h"

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

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

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