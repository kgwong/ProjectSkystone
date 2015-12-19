#ifndef SNAKE_AI_COMPONENT_H
#define SNAKE_AI_COMPONENT_H

#include "AIComponent.h"

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

	virtual void start(Level& level);
	virtual void update(Level& level);

private:

	int velocity_;
	PhysicsComponent* physics_;
	Point cornerPosition_;
};

#endif