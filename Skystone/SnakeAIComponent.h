#ifndef SNAKE_AI_COMPONENT_H
#define SNAKE_AI_COMPONENT_H
#include "AIComponent.h"


class SnakeAIComponent :
	public AIComponent
{

public:
	static const int DEFAULT_X_DIST = 100;
	static const int DEFAULT_Y_DIST = 100;
	static const int DEFAULT_VELOCITY = 3;



public:

	SnakeAIComponent();
	virtual ~SnakeAIComponent();

	virtual void start(GameObject& owner, Level& level);
	virtual void update(GameObject& owner, Level& level);

private:

	int velocity_;
	PhysicsComponent* physics_;
	Point cornerPosition_;
};

#endif