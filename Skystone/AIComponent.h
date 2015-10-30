#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "Component.h"

class AIComponent : public Component
{
public:
	virtual ~AIComponent() {};

	virtual void start(GameObject& owner, Level& level) {};
	virtual void update(GameObject& owner, Level& level) {};
};

#endif //AI_COMPONENT_H