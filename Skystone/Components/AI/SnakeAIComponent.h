#ifndef SNAKE_AI_COMPONENT_H
#define SNAKE_AI_COMPONENT_H

#include "AIComponent.h"

//use floats for position/dist/vel/accel! Delete this comment after adapting change

class PhysicsComponent;

class SnakeAIComponent :
	public AIComponent
{

public:
	static const int DEFAULT_X_DIST = 100;
	static const int DEFAULT_Y_DIST = 100;
	static const int DEFAULT_VELOCITY = 3;



public:

	SnakeAIComponent(GameObject& owner);
	virtual ~SnakeAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:

	int velocity_;
	PhysicsComponent* physics_;
	Point cornerPosition_;
};

#endif