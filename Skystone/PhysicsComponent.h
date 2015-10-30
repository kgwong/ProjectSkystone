#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Axis.h"
#include "Component.h"

class Level;
class GameObject;
class ColliderComponent;


class PhysicsComponent : public Component
{
public:
	static const int GRAVITY = 1;
	static const int TERMINAL_VELOCITY = 20;

public:
	PhysicsComponent();
	virtual ~PhysicsComponent();

	virtual void start(GameObject& owner, Level& level);
	virtual void update(GameObject& owner, Level& level);

	void setVelX(int velX);
	void setVelY(int velY);
	void setAccelX(int accelX);
	void setAccelY(int accelY);

	int getVelX() const;
	int getVelY() const;
	int getAccelX() const;
	int getAccelY() const;

	bool isMovingUp() const;
	bool isMovingDown() const;
	bool isMovingLeft() const;
	bool isMovingRight() const;

	bool isFalling() const; 

	void enableGravity(bool gravity);

private:
	int _velX, _velY;
	int _accelX, _accelY;

	bool _gravityEnabled;
	bool _falling;

	ColliderComponent* collider_;

	void updatePosition(GameObject& owner, Axis axis);
	void updatePositionAfterCollision(GameObject& owner, Level& level, Axis axis);
	void handleCollision(GameObject& owner, GameObject& other, Level& level, Axis axis);

private:
	void enactGravity();

};

#endif //PHYSICSCOMPONENT_H