#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "ColliderComponent.h"
#include "Axis.h"

struct LevelEntities;
class GameObject;

class PhysicsComponent
{
public:
	static const int GRAVITY = 1;
	static const int TERMINAL_VELOCITY = 20;

public:
	PhysicsComponent();
	virtual ~PhysicsComponent();

	void update(GameObject& owner, LevelEntities& entities, ColliderComponent* collider);

	void setVelX(int velX);
	void setVelY(int velY);
	void setAccelX(int accelX);
	void setAccelY(int accelY);

	int getVelX();
	int getVelY();
	int getAccelX();
	int getAccelY();

	bool isMovingUp();
	bool isMovingDown();
	bool isMovingLeft();
	bool isMovingRight();

	bool isFalling(); 

	void enableGravity(bool gravity);

private:
	int _velX, _velY;
	int _accelX, _accelY;

	bool _gravityEnabled;
	bool _falling;

	void updatePosition(GameObject& owner, Axis axis);
	void handleCollision(GameObject& owner, GameObject& other, ColliderComponent* collider, Axis axis);

private:
	void enactGravity();

};

#endif //PHYSICSCOMPONENT_H