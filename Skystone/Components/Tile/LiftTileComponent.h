#ifndef LIFT_TILE_COMPONENT_H
#define LIFT_TILE_COMPONENT_H

#include "GameTypes/Point.h"
#include "SpecialTileComponent.h"

class PhysicsComponent;

class LiftTileComponent : public SpecialTileComponent
{
public:
	static const int DEFAULT_X_RADIUS = 25;
	static const int DEFAULT_DELAY = 7;
	static const int DEFAULT_LIFT = 3;


	LiftTileComponent(GameObject& owner);
	virtual ~LiftTileComponent();


	virtual void start(Scene& scene);
	virtual void update(Scene& scene);
	virtual void handleEvent(const CollisionEvent& other);




private:
	PhysicsComponent* physics_;
	PhysicsComponent* playerPhysics_;
	ColliderComponent* playerCollider_;
	ColliderComponent* collider_;
	int xRadius_;

	int delay_;
	int time_;
	int lift_;
	float tileLeft_;
	float tileRight_;
	

};

#endif //#LIFT_COMPONENT_H