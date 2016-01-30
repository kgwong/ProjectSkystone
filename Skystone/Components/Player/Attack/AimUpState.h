#ifndef AIM_UP_STATE_H
#define AIM_UP_STATE_H

#include "PlayerAimState.h"

class AimUpState : public PlayerAimState
{
public:
	AimUpState();
	virtual ~AimUpState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player) {};

	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player);

	virtual double getAngle();
	virtual std::string name();

private:
	enum class Direction
	{
		NONE, LEFT, RIGHT
	};

private: 
	Direction dir_;
};

#endif //AIM_UP_STATE_H