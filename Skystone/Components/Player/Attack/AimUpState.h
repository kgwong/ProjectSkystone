#ifndef AIM_UP_STATE_H
#define AIM_UP_STATE_H

#include "PlayerAimState.h"

class PlayerControlComponent;
class PhysicsComponent;
class SpriteRenderer;

class AimUpState : public PlayerAimState
{
public:
	AimUpState(GameObject& owner);
	virtual ~AimUpState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual std::string name();

	virtual double getAngle();

private:
	enum class Direction
	{
		NONE, LEFT, RIGHT
	};

private: 
	Direction dir_;

	PlayerControlComponent* controlComponent_;
	PhysicsComponent* physics_;
	SpriteRenderer* renderer_;
};

#endif //AIM_UP_STATE_H