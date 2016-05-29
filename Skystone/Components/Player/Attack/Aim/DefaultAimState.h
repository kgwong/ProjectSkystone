#ifndef DEFAULT_AIM_STATE_H
#define DEFAULT_AIM_STATE_H

#include "PlayerAimState.h"

class PlayerControlComponent;

class DefaultAimState : public PlayerAimState
{
public:
	DefaultAimState(GameObject& owner);
	virtual ~DefaultAimState();

	virtual void onEnter(Scene& scene);

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual double getAngle();

	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;

};

#endif //DEFAULT_AIM_STATE_H