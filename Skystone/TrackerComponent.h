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
	static const int DEFAULT_X_VELOCITY = 0;
	static const int RUNNING_X_VELOCITY = 2;
	static const int DEFAULT_RADIUS = 150;

public:
	TrackerComponent();
	virtual ~TrackerComponent();

	//NEED FOR EVERY AICOMPONENT
	virtual void start(GameObject& owner, Level& level);
	virtual void update(GameObject& owner, Level& level);

	EnemyState getEnemyState();
	void setEnemyState(EnemyState state);

	void followCommand(int player_direction);
	void fleeCommand(int player_direction);

private:
	int xVelocity_;
	int radius_;
	EnemyState enemyState_;
	//need it this always ~ maybe put it the base class.
	PhysicsComponent* physics_;

};

#endif

