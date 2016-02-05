#ifndef LIFT_TILE_COMPONENT_H
#define LIFT_TILE_COMPONENT_H

#include "Point.h"
#include "SpecialTileComponent.h"

class PhysicsComponent;

class LiftTileComponent : public SpecialTileComponent
{
public:
	static const int DEFAULT_X_RADIUS = 25;
	static const int DEFAULT_DELAY = 7;


	LiftTileComponent(GameObject& owner);
	virtual ~LiftTileComponent();


	virtual void start(Level& level);
	virtual void update(Level& level);
	virtual void handleEvent(const CollisionEvent& other);




private:
	PhysicsComponent* physics_;
	PhysicsComponent* playerPhysics_;
	int xRadius_;

	int delay_;
	int time_;
	

};

#endif //#LIFT_COMPONENT_H