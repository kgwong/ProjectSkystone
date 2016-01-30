#ifndef STUN_STATE_H
#define STUN_STATE_H

#include "PlayerState.h"

class StunState : public PlayerState
{
public:
	StunState();
	virtual ~StunState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player);

	virtual std::string name() { return "Stunned"; }

private:
	bool firstUpdate_; // hack
};

#endif //STUN_STATE_H