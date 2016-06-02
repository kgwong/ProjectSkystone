#ifndef SWING_STATE_H
#define SWING_STATE_H

#include "Components/Player/Movement/PlayerState.h"
#include "Components/Player/PlayerControlComponent.h"

class SwingState :
	public PlayerState
{
public:
	static const float ANGLE_RANGE;
	static const float RESTING_ANGLE;
	static const float STARTING_SPEED;
	static const float MAX_SPEED;
public:
	SwingState(GameObject& owner);
	virtual ~SwingState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);
	virtual void handleEvent(const CollisionEvent& e);
	virtual std::string name();

	void resetVariables();
	bool verifiedState(Scene& scene);

private:
	float xSpeed_;
	float angle_;
	int xDirection_;
	int orient_;

	Point hookPosition_;
	Point swingPosition_;
	Point oldPosition_;
	float radius_;

	float swingTime_;
	float damp_;
	bool keyHeld_;
	float timer_;
	float angleRange_;
	bool enemyHit_;

	PlayerControlComponent* stateManager_;
	PhysicsComponent* physics_;

};

#endif

