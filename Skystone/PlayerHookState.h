#ifndef PLAYER_HOOK_STATE
#define PLAYER_HOOK_STATE

#include "InputComponent.h"
#include "AimState.h"
class PlayerHookState :
	public InputComponent
{
public:
	static const AimState DEFAULT_AIM_STATE = AimState::RIGHT;
public:
	PlayerHookState(GameObject& owner);
	~PlayerHookState();

	virtual void handleInput(SDL_Event& e);
	void update(Level& level);

private:
	double _degrees;
	bool _launched;
	AimState _currentAimState;

};

#endif

