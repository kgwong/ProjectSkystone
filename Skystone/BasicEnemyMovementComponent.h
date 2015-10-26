#ifndef BASIC_ENEMY_MOVEMENT_COMPONENT_H
#define BASIC_ENEMY_MOVEMENT_COMPONENT_H

#include "Component.h"

class PhysicsComponent;

class BasicEnemyMovementComponent :	public Component
{
public:
	static const int DEFAULT_SPEED = 1;

public:
	BasicEnemyMovementComponent();
	BasicEnemyMovementComponent(int speed);
	virtual ~BasicEnemyMovementComponent();

	virtual void start(GameObject& owner);
	virtual void update(GameObject& owner);

private:
	int speed_; 
	int oldEnemyPosition_;

	PhysicsComponent* physics_;
};

#endif //BASIC_ENEMY_MOVEMENT_COMPONENT_H