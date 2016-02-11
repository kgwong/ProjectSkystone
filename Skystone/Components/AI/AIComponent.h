#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "Components/Component.h"
#include "GameTypes/Point.h"

class AIComponent : public Component
{
public:
	AIComponent(GameObject& owner);
	virtual ~AIComponent();

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const ComponentEvent& e);

	virtual Component::Type getType() final;

	static bool isNearby(int dist, int radius);


};

#endif //AI_COMPONENT_H