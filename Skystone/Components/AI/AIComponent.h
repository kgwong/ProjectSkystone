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
	virtual void handleEvent(const OnDeathEvent& e);

	virtual Component::Type getType() final;
	virtual void fireProjectile(float xDist, float yDist, float playerSide, float offset, Scene& scene, float speed);

	static bool isNearby(float dist, float radius);


};

#endif //AI_COMPONENT_H