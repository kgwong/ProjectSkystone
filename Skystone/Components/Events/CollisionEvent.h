#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include "ComponentEvent.h"

class GameObject;
class ColliderComponent;

class CollisionEvent : public ComponentEvent
{
public:
	CollisionEvent(Scene& scene, GameObject& other, ColliderComponent& otherCollider);
	virtual ~CollisionEvent();

	GameObject& getOtherObject() const;
	ColliderComponent& getOtherCollider() const;

private:
	GameObject& other_;
	ColliderComponent& otherCollider_;
};

#endif //COLLISION_EVENT_H