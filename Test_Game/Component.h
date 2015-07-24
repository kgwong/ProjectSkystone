#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component
{
public:
	virtual ~Component() {};
	//virtual void update() = 0;
	virtual void* getAttribute(const std::string& name) { return nullptr; };
};

#endif //COMPONENT_H