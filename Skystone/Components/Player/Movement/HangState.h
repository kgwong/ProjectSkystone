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
	HangState();
	virtual ~HangState();

	virtual void onEnter(Scene& scene, GameObject& player);
	virtual void onExit(Scene& scene, GameObject& player);
	virtual void handleInput(Scene& scene, GameObject& player, SDL_Event& e);
	virtual void update(Scene& scene, GameObject& player);
	Point SwingVector();
	Point OldPlayerPos();

	virtual std::string name() { return "Hang"; }
private:
	Point swingVector_;
	Point oldPlayerPos_;
	int direction_;
	float currentAngle_;

	Point hookPosition_;
	float radius_;

	float oldPlayerYVelocity;

};

#endif

