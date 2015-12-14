#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include "Level.h"

class Component
{
public:
	Component(GameObject& owner)
		:owner_(owner)
	{

	}
	virtual ~Component() {};

	virtual void start(Level& level) = 0;
	virtual void update(Level& level) = 0;

	bool owned() { return owned_; }
	void disown() { owned_ = false; }

protected:
	GameObject& owner_;
	bool owned_;
};

#endif //COMPONENT_H