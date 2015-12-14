#ifndef RANDOM_JUMPER_COMPONENT_H
#define RANDOM_JUMPER_COMPONENT_H

#include "AIComponent.h"

class PhysicsComponent;

class RandomJumperComponent : public AIComponent
{
public:
	static const int DEFAULT_TIME_INTERVAL = 100;
	static const int DEFAULT_JUMP_VELOCITY = -15;
	static const int DEFAULT_X_VELOCITY = 5;

public:
	RandomJumperComponent(GameObject& owner);
	virtual ~RandomJumperComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	int timeInterval_;
	PhysicsComponent* physics_;
	int jumpVelocity_;
	int xVelocity_;
};

#endif //RANDOM_JUMPER_COMPONENT_H
