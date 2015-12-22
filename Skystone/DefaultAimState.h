#ifndef DEFAULT_AIM_STATE_H
#define DEFAULT_AIM_STATE_H

#include "PlayerAimState.h"

class DefaultAimState : public PlayerAimState
{
public:
	DefaultAimState();
	virtual ~DefaultAimState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player) ;

	virtual double getAngle();
	virtual std::string name();

private:
	bool facingRight_;
};

#endif //DEFAULT_AIM_STATE_H