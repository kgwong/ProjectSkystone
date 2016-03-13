#ifndef AI_JUMP_H
#define AI_JUMP_H
#include "AIComponent.h"

//use floats for position/dist/vel/accel! Delete this comment after adapting change

class PhysicsComponent;

class AIjump :
	public AIComponent
{
public:
	static const int DEFAULT_JUMP_VELOCITY = -5;
	static const int JUMP_INTERVAL = 10;
	static const int FALL_VELOCITY = 5;

public:
	AIjump(GameObject& owner);
	virtual ~AIjump();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	PhysicsComponent* physics_;
	int jumpvelocity_;
	
	int timer_;

};
#endif

