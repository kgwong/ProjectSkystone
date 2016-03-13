#ifndef BASIC_ENEMY_MOVEMENT_COMPONENT_H
#define BASIC_ENEMY_MOVEMENT_COMPONENT_H

#include "AIComponent.h"

class PhysicsComponent;

class BasicEnemyMovementComponent :	public AIComponent
{
public:
	static const float DEFAULT_SPEED;

public:
	BasicEnemyMovementComponent(GameObject& owner);
	BasicEnemyMovementComponent(GameObject& owner, float speed);
	virtual ~BasicEnemyMovementComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	float speed_; 
	float oldEnemyPosition_;

	PhysicsComponent* physics_;
};

#endif //BASIC_ENEMY_MOVEMENT_COMPONENT_H