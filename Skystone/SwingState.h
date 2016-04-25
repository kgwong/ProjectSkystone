#ifndef SWING_STATE_H
#define SWING_STATE_H
#include "Components\Player\Movement\PlayerState.h"
class SwingState :
	public PlayerState
{
public:
	static const float MAX_ANGLE;
	SwingState(GameObject& owner);
	virtual ~SwingState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual std::string name();

	virtual void handleEvent(const CollisionEvent& e);

	Point swingPosition();


private:
	float xSpeed_;
	float currentAngle_;
	int xDirection_;

	Point hookPosition_;
	Point swingPosition_;
	Point oldPosition_;
	float radius_;

	bool tileHit_;
	bool tileLeft_;
	bool tileRight_;

};

#endif

