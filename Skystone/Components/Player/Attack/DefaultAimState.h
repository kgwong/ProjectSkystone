#ifndef DEFAULT_AIM_STATE_H
#define DEFAULT_AIM_STATE_H

#include "PlayerAimState.h"

class DefaultAimState : public PlayerAimState
{
public:
	DefaultAimState();
	virtual ~DefaultAimState();

	virtual void onEnter(Scene& scene, GameObject& player);
	virtual void onExit(Scene& scene, GameObject& player);
	
	virtual void handleInput(Scene& scene, GameObject& player, SDL_Event& e);
	virtual void update(Scene& scene, GameObject& player) ;

	virtual double getAngle();
	virtual std::string name();

private:
	bool facingRight_;
};

#endif //DEFAULT_AIM_STATE_H