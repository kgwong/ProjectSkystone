#ifndef FALLING_AI_COMPONENT_H
#define FALLING_AI_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;


class FallingAIComponent :
	public AIComponent
{
	enum class STATE
	{
		NEUTRAL,
		FALLING,
		RISING,
		DELAY
	};


public:
	static const float DEFAULT_Y_VELOCITY;
	static const float DEFAULT_RISE_VELOCITY;
	static const float DEFAULT_X_RADIUS;
	static const float DEFAULT_Y_RADIUS;
	static const int DEFAULT_TIME_INTERVAL = 100;

public:
	FallingAIComponent(GameObject& owner);
	virtual ~FallingAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);
	virtual void handleEvent(const CollisionEvent& e);

private:
	float yVelocity_;
	Point upperLeftCorner_;
	Point upperRightCorner_;
	Point playerPos_;
	PhysicsComponent* physics_;

	int timer_;
	STATE state_;
};

#endif