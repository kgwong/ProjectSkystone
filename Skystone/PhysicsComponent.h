#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Axis.h"
#include "Component.h"

class ColliderComponent;

class PhysicsComponent : public Component
{
public:
	static const int GRAVITY = 1;
	static const int TERMINAL_VELOCITY = 20;

public:
	PhysicsComponent(GameObject& owner);
	virtual ~PhysicsComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

	virtual Component::Type getType() final;

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
	bool gravityEnabled();

private:
	int velX_, velY_;
	int accelX_, accelY_;

	bool gravityEnabled_;
	bool falling_;

	ColliderComponent* collider_;

private:
	void enactGravity();

	void updatePosition(GameObject& owner, Level& level, Axis axis);
	void correctPositionAfterCollision(GameObject& owner, Level& level, Axis axis);
	void checkCollisions(GameObject& owner, Level& level);
	void callOnCollision(GameObject& owner, GameObject& other, Level& level);
	void correctPosition(GameObject& owner, GameObject& other, Level& level, Axis axis);

};

#endif //PHYSICSCOMPONENT_H