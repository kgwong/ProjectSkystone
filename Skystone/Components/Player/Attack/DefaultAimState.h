#ifndef DEFAULT_AIM_STATE_H
#define DEFAULT_AIM_STATE_H

#include "PlayerAimState.h"

class DefaultAimState : public PlayerAimState
{
public:
	DefaultAimState(GameObject& owner);
	virtual ~DefaultAimState();

	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual double getAngle();

	virtual std::string name();

private:
	bool facingRight_;
};

#endif //DEFAULT_AIM_STATE_H