#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "Components/NonUpdatingComponent.h"

class HealthComponent;
class PhysicsComponent;

class PlayerComponent : public NonUpdatingComponent
{
public:
	PlayerComponent(GameObject& owner);
	virtual ~PlayerComponent();

	virtual void start(Scene& scene);

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const OnDeathEvent& e);
	virtual void handleEvent(const DamageTakenEvent& e);

private:
	HealthComponent* health_;
	PhysicsComponent* physics_;
};

#endif //PLAYER_COMPONENT_H