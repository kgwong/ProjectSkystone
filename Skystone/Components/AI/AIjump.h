#ifndef AI_JUMP_H
#define AI_JUMP_H
#include "AIComponent.h"

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

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	PhysicsComponent* physics_;
	int jumpvelocity_;
	
	int timer_;

};
#endif

