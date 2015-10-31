#ifndef RANDOM_JUMPER_COMPONENT_H
#define RANDOM_JUMPER_COMPONENT_H

#include "AIComponent.h"

class PhysicsComponent;

class RandomJumperComponent : public AIComponent
{
public:
	static const int DEFAULT_TIME_INTERVAL = 100;

public:
	RandomJumperComponent();
	virtual ~RandomJumperComponent();
	void start(GameObject& owner, Level& level);
	void update(GameObject& owner, Level& level);
private:
	int timeInterval_;
	PhysicsComponent* physics_;
	int oldVelX_;
	int oldVelY_;
};

#endif //RANDOM_JUMPER_COMPONENT_H
