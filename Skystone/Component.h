#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
//#include "Level.h"
//class GameObject;
class Level;

class Component
{
public:
	virtual ~Component() {};

	virtual void start(GameObject& owner, Level& level) = 0;
	virtual void update(GameObject& owner, Level& level) = 0;
};

#endif //COMPONENT_H