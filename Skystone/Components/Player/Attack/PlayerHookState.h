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
	void update(Scene& scene);
	double getDegrees();
	void setLaunched(bool b);
	bool hasLaunched();
	bool isActiveHook();
	SDL_Keycode getKeyInput();

private:
	double _degrees;
	bool _launched;
	bool _hookActive;
	AimState _currentAimState;
	SDL_Keycode _keyInput;
};

#endif

