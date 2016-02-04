#ifndef BASIC_ENEMY_MOVEMENT_COMPONENT_H
#define BASIC_ENEMY_MOVEMENT_COMPONENT_H

#include "AIComponent.h"

class PhysicsComponent;

class BasicEnemyMovementComponent :	public AIComponent
{
public:
	static const int DEFAULT_SPEED = 1;

public:
	BasicEnemyMovementComponent(GameObject& owner);
	BasicEnemyMovementComponent(GameObject& owner, int speed);
	virtual ~BasicEnemyMovementComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	int speed_; 
	int oldEnemyPosition_;

	PhysicsComponent* physics_;
};

#endif //BASIC_ENEMY_MOVEMENT_COMPONENT_H