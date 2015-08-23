#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component
{
public:
	virtual ~Component() {};
	virtual void update(GameObject& owner) {};
};

#endif //COMPONENT_H