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
	static const int RUNNING_X_VELOCITY = 1;
	static const int DEFAULT_RADIUS = 150;

public:
	TrackerComponent();
	virtual ~TrackerComponent();

	virtual void start(GameObject& owner,Level& level);
	virtual void update(GameObject& owner,Level& level);
	
	EnemyState getEnemyState();

private:
	int xVelocity_;
	int radius_;
	EnemyState enemyState_;
	PhysicsComponent* physics_;
};

#endif

