#ifndef WALKING_STATE_H
#define WALKING_STATE_H

#include "PlayerState.h"
#include "GameTypes/Direction.h"

class PlayerControlComponent;
class PhysicsComponent;
class SpriteAnimator;

class WalkingState : public PlayerState
{
public:
	static const float JUMP_VELOCITY;
	static const float WALK_VELOCITY;

	enum class SubState
	{
		LEFT,
		IDLE,
		RIGHT
	};


public:
	WalkingState(GameObject& owner);
	virtual ~WalkingState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual std::string name() { return "WalkingState"; }

	virtual SubState getSubState();

private:
	PlayerControlComponent* controlComponent_;
	PhysicsComponent* physics_;
	SpriteAnimator* animator_;
	SubState subState_;

private:
	void changeSubState(SubState newSubState);
	std::string subStateToString(SubState subState);
};

#endif // WALKING_STATE_H