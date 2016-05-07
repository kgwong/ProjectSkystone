#ifndef PLAYER_MOVEMENT_STATE_H
#define PLAYER_MOVEMENT_STATE_H

#include "Components/InputComponent.h"

#include "PlayerState.h"

#include <memory>

class PlayerMovementState : public InputComponent
{
public:
	PlayerMovementState(GameObject& owner);
	virtual ~PlayerMovementState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	void changeState(Scene& scene, const std::string& stateName);
	PlayerState* getState();
	virtual void handleEvent(const CollisionEvent& e);

	void setCanSwing(bool swing);
	bool canSwing;

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

	std::unordered_map<std::string, std::shared_ptr<PlayerState>> states_;

private:
	PlayerState* getStateFromName(const std::string& name);
	void addState(std::shared_ptr<PlayerState> state);
};

#endif //PLAYER_MOVEMENT_STATE_H