#ifndef PLAYER_HOOK_STATE
#define PLAYER_HOOK_STATE

#include "Components/InputComponent.h"
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
	double getDegrees();
	void setLaunched(bool b);

private:
	double _degrees;
	bool _launched;
	AimState _currentAimState;
};

#endif

