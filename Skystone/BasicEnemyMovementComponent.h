#ifndef BASIC_ENEMY_MOVEMENT_H
#define BASIC_ENEMY_MOVEMENT_H

#include "Component.h"

class BasicEnemyMovementComponent :
	public Component
{
public:
	static const int DEFAULT_SPEED = 1;

	BasicEnemyMovementComponent();
	BasicEnemyMovementComponent(int speed);

	virtual ~BasicEnemyMovementComponent();

	virtual void update(GameObject& owner);

private:
	int speed_; 
	int oldEnemyPosition;
	bool initialized;
};

#endif //BASIC_ENEMY_MOVEMENT_H