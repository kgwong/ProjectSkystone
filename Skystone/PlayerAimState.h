#ifndef PLAYER_AIM_STATE_H
#define PLAYER_AIM_STATE_H

#include "PlayerState.h"

class PlayerAimState : public PlayerState
{
public:
	PlayerAimState();
	virtual ~PlayerAimState();

	virtual double getAngle() = 0;
};

#endif //PLAYER_AIM_STATE_H