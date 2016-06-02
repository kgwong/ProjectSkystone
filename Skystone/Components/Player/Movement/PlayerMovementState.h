#ifndef PLAYER_MOVEMENT_STATE_H
#define PLAYER_MOVEMENT_STATE_H

#include "Components/InputComponent.h"

#include "PlayerState.h"

#include <memory>

//holds fields that are shared between swing and hang state.
//struct sharedVariables
//{
//	int direction;
//	float speed;
//	float angle;
//	float radius;
//};

class PlayerMovementState : public InputComponent
{
public:
	PlayerMovementState(GameObject& owner);
	virtual ~PlayerMovementState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	void changeState(Scene& scene, const std::string& stateName);
	void resetState();
	PlayerState* getState();
	PlayerState* getPrevState();
	virtual void handleEvent(const CollisionEvent& e);

	void setDirection(int dir);
	void setSpeed(float s);
	void setAngle(float a);
	void setRadius(float r);

	int direction;
	float speed;
	float angle;
	float radius;

private:
	PlayerState* currentState_;
	PlayerState* previousState_;

	std::unordered_map<std::string, std::shared_ptr<PlayerState>> states_;

private:
	PlayerState* getStateFromName(const std::string& name);
	void addState(std::shared_ptr<PlayerState> state);
};

#endif //PLAYER_MOVEMENT_STATE_H