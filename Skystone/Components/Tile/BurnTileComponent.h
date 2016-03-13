#ifndef BURN_TILE_COMPONENT_H
#define BURN_TILE_COMPONENT_H

#include "SpecialTileComponent.h"

class PhysicsComponent;
class HealthComponent;
class DamageComponent;

class BurnTileComponent :
	public SpecialTileComponent
{
public:
	static const int DEFAULT_DAMAGE = 2;
	static const int DEFAULT_DELAY = 25;
	static const int DEFAULT_SLOW = 4;





	BurnTileComponent(GameObject& owner);
	virtual ~BurnTileComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);
	virtual void handleEvent(const CollisionEvent& other);

private:
	PhysicsComponent *playerPhysics_;
	PhysicsComponent *physics_;
	HealthComponent *health_;
	DamageComponent *damage_;
	int damage_value_;
	int delay_;
	int slow_;
	int time_;
	
};

#endif //#BURN_TILE_COMPONENT_H