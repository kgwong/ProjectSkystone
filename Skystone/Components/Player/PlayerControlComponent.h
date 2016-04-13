#ifndef PLAYER_CONTROL_COMPONENT_H
#define PLAYER_CONTROL_COMPONENT_H

#include "Components/InputComponent.h"
#include "Movement/PlayerMovementState.h"
#include "Attack/PlayerAttackState.h"

//-------Harvey's include-----///
#include "Attack/PlayerHookState.h"
#include "ATtack/HookStateManager.h"

class PlayerControlComponent : public InputComponent
{
public:
	PlayerControlComponent(GameObject& owner);
	virtual ~PlayerControlComponent();

	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	void changeMovementState(Scene& scene, const std::string& stateName);
	void changeAttackState(Scene& scene, const std::string& stateName);

	//----harvey function----///
	void changeHookState(Scene& scene, const std::string& stateName);
	PlayerHookState HookState();
	PlayerMovementState& MovementState();
	PlayerAttackState& AttackState();
	virtual void handleEvent(const CollisionEvent& e);

	//will delete later.
	bool isHookActive();
	SDL_Keycode HookKeyInput;

private:
	PlayerMovementState movement_;
	PlayerAttackState attack_;

	//--harvey hook--//
	PlayerHookState hooker_;
};

#endif //PLAYER_CONTROL_COMPONENT_H