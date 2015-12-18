#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "NonUpdatingComponent.h"

class HealthComponent;
class PhysicsComponent;

class PlayerComponent : public NonUpdatingComponent
{
public:
	PlayerComponent(GameObject& owner);
	virtual ~PlayerComponent();

	virtual void start(Level& level);

	virtual void handleEvent(const ComponentEvent& e);
	virtual void handleEvent(const CollisionEvent& e);

private:
	HealthComponent* health_;
	PhysicsComponent* physics_;
};

#endif //PLAYER_COMPONENT_H