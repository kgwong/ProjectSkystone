#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include "Level.h"

class Component
{
public:
	virtual ~Component() {};

	virtual void start(GameObject& owner, Level& level) = 0;
	virtual void update(GameObject& owner, Level& level) = 0;

	bool owned() { return owned_; }
	void disown() { owned_ = false; }
protected:
	bool owned_;
};

#endif //COMPONENT_H