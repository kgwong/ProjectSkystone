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
	static const float MIN_ROPE_LENGTH;
	static const float MAX_ROPE_LENGTH;
public:
	HangState(GameObject& owner);
	virtual ~HangState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void handleEvent(const CollisionEvent& e);
	virtual void update(Scene& scene);


	virtual std::string name() { return "Hang"; }
private:
	Point hookPosition_;
	Point hangPosition_;
	float ropeLength_;
	float ySpeed_;//how fast player can increase/decrease rope length.
	int yDirection_;

};

#endif

