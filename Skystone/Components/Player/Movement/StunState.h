#ifndef STUN_STATE_H
#define STUN_STATE_H

#include "PlayerState.h"

class StunState : public PlayerState
{
public:
	StunState(GameObject& owner);
	virtual ~StunState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual std::string name();

private:
	bool firstUpdate_; // hack
};

#endif //STUN_STATE_H