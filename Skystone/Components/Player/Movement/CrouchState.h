#ifndef CROUCH_STATE_H
#define CROUCH_STATE_H

#include "PlayerState.h"

class CrouchState : public PlayerState
{
public:
	CrouchState(GameObject& owner);
	virtual ~CrouchState();



	virtual std::string name();
};

#endif //CROUCH_STATE_H
