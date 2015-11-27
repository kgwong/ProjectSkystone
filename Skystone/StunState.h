#ifndef STUN_STATE_H
#define STUN_STATE_H

#include "PlayerState.h"

class StunState : public PlayerState
{
public:
	StunState();
	virtual ~StunState();

	virtual void onEnter(Player& player);
	virtual void onExit(Player& player);
	virtual void handleInput(Player& player, SDL_Event& e);
	virtual void update(Player& player);

	virtual std::string name() { return "Stunned"; }

private:
	bool firstUpdate_; // hack
};

#endif //STUN_STATE_H