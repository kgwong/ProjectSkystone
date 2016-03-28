#ifndef SNAKE_AI_COMPONENT_H
#define SNAKE_AI_COMPONENT_H

#include "AIComponent.h"

//use floats for position/dist/vel/accel! Delete this comment after adapting change

class PhysicsComponent;

class SnakeAIComponent :
	public AIComponent
{

public:
	const float DEFAULT_X_DIST = 100;
	const float DEFAULT_Y_DIST = 100;
	const float DEFAULT_VELOCITY = 3;



public:

	SnakeAIComponent(GameObject& owner);
	virtual ~SnakeAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:

	float velocity_;
	PhysicsComponent* physics_;
	Point cornerPosition_;
};

#endif