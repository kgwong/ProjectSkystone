#ifndef PLAYER_CONTROL_COMPONENT_H
#define PLAYER_CONTROL_COMPONENT_H

#include "InputComponent.h"
#include "PlayerMovementState.h"
#include "PlayerAttackState.h"

//-------Harvey's include-----///
#include "PlayerHookState.h"

class PlayerControlComponent : public InputComponent
{
public:
	PlayerControlComponent(GameObject& owner);
	virtual ~PlayerControlComponent();

	virtual void handleInput(SDL_Event& e);
	virtual void update(Level& level);

	void changeMovementState(PlayerState* state);
	void changeAttackState(PlayerAimState* state);

	//----harvey function----///
	//void changeHookState(PlayerHookState*)


private:
	PlayerMovementState movement_;
	PlayerAttackState attack_;

	//--harvey hook--//
	PlayerHookState hooker_;
};

#endif //PLAYER_CONTROL_COMPONENT_H