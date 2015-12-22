#ifndef PLAYER_CONTROL_COMPONENT_H
#define PLAYER_CONTROL_COMPONENT_H

#include "InputComponent.h"
#include "PlayerMovementState.h"
#include "PlayerAttackState.h"

class PlayerControlComponent : public InputComponent
{
public:
	PlayerControlComponent(GameObject& owner);
	virtual ~PlayerControlComponent();

	virtual void handleInput(SDL_Event& e);
	virtual void update(Level& level);

	void changeMovementState(PlayerState* state);
	void changeAttackState(PlayerAimState* state);

private:
	PlayerMovementState movement_;
	PlayerAttackState attack_;
};

#endif //PLAYER_CONTROL_COMPONENT_H