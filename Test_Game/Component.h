#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component
{
public:
	virtual ~Component() {};
	virtual void update(GameObject& owner) {};
	virtual void* getAttribute(const std::string& name) { return nullptr; };
};

#endif //COMPONENT_H