#ifndef RANDOM_JUMPER_COMPONENT_H
#define RANDOM_JUMPER_COMPONENT_H

#include "AIComponent.h"

class PhysicsComponent;

class RandomJumperComponent : public AIComponent
{
public:
	static const int DEFAULT_TIME_INTERVAL = 100; // use Time::
	static const float DEFAULT_JUMP_VELOCITY;
	static const float DEFAULT_X_VELOCITY;

public:
	RandomJumperComponent(GameObject& owner);
	virtual ~RandomJumperComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	int timeInterval_;
	PhysicsComponent* physics_;
	float jumpVelocity_;
	float xVelocity_;
};

#endif //RANDOM_JUMPER_COMPONENT_H
