#ifndef AIM_DIAGONAL_STATE
#define AIM_DIAGONAL_STATE

#include "PlayerAimState.h"

class PlayerControlComponent;

class AimDiagonalState : public PlayerAimState
{
public:
	AimDiagonalState(GameObject& owner);
	virtual ~AimDiagonalState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual double getAngle();
	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;
};

#endif //AIM_DIAGONAL_STATE_H
