#ifndef HANG_STATE_H
#define HANG_STATE_H
#include "Components\Player\Movement\PlayerState.h"
class HangState :
	public PlayerState
{
	//CONSTANTS:
public:
	static const float MAX_ANGLE; 
	static const float DEFAULT_SPEED;
	static const float MAX_SPEED;
public:
	HangState(GameObject& owner);
	virtual ~HangState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);
	Point SwingVector();
	Point OldPlayerPos();
	int getDirection();

	virtual std::string name() { return "Hang"; }
private:
	Point swingVector_;
	Point oldPlayerPos_;
	int direction_;
	float currentAngle_;

	Point hookPosition_;
	float radius_;
	float currentSpeed_;

	float oldPlayerYVelocity;

};

#endif

