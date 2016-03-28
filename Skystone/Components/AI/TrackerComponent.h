#ifndef TRACKER_COMPONENT_H
#define TRACKER_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;

enum EnemyState
{
	NEUTRAL,
	FOLLOWER,
	COWARD
};

class TrackerComponent :
	public AIComponent
{

public:
	static const float DEFAULT_X_VELOCITY;
	static const float RUNNING_X_VELOCITY;
	static const float DEFAULT_RADIUS;

public:
	TrackerComponent(GameObject& owner);
	virtual ~TrackerComponent();

	//NEED FOR EVERY AICOMPONENT
	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	EnemyState getEnemyState();
	void setEnemyState(EnemyState state);

	void followCommand(int player_direction);
	void fleeCommand(int player_direction);

private:
	float xVelocity_;
	float radius_;
	EnemyState enemyState_;
	//need it this always ~ maybe put it the base class.
	PhysicsComponent* physics_;

};

#endif

