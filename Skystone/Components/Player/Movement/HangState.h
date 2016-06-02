#ifndef HANG_STATE_H
#define HANG_STATE_H
#include "Components\Player\Movement\PlayerState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "Game/GameTime.h"

class HangState :
	public PlayerState
{
	//CONSTANTS:
public:
	static const float RESTING_ANGLE;
	static const float MAX_SPEED;
	static const float STARTING_SPEED;
public:
	HangState(GameObject& owner);
	virtual ~HangState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void handleEvent(const CollisionEvent& e);
	virtual void update(Scene& scene);

	void resetVariables();
	bool verifiedState(Scene& scene);//checks to see if player is in the correct state.
	void increaseSpeed();
	int swingDirection();

	virtual std::string name();
private:
	float angle_;
	Point playerPos_;
	Point hookPosition_;
	float radius_;
	int yDirection_;
	float ySpeed_;

	PhysicsComponent* physics_;
	PlayerControlComponent* stateManager_;

};

#endif

