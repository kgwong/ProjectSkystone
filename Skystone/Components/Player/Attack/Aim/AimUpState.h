#ifndef AIM_UP_STATE_H
#define AIM_UP_STATE_H

#include "PlayerAimState.h"

class PlayerControlComponent;

class AimUpState : public PlayerAimState
{
public:
	AimUpState(GameObject& owner);
	virtual ~AimUpState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual double getAngle();
	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;
};

#endif //AIM_UP_STATE_H
