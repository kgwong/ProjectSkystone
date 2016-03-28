#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "GameTypes/Axis.h"
#include "Components/Component.h"

class ColliderComponent;

class PhysicsComponent : public Component
{
public:
	static const float GRAVITY;
	static const float TERMINAL_VELOCITY;

public:

	PhysicsComponent(GameObject& owner);
	virtual ~PhysicsComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual Component::Type getType() final;
	
	void setVelX(float velX);
	void setVelY(float velY);
	void setAccelX(float accelX);
	void setAccelY(float accelY);

	float getVelX() const;
	float getVelY() const;
	float getAccelX() const;
	float getAccelY() const;

	bool isMovingUp() const;
	bool isMovingDown() const;
	bool isMovingLeft() const;
	bool isMovingRight() const;

	bool isFalling() const; 

	void enableGravity(bool gravity);
	bool gravityEnabled();

private:
	float velX_, velY_;
	float accelX_, accelY_;

	bool gravityEnabled_;
	bool falling_;

	ColliderComponent* collider_;

private:
	void enactGravity();

	void updatePosition(GameObject& owner, Scene& scene, Axis axis);
	void correctPositionAfterCollision(GameObject& owner, Scene& scene, Axis axis);
	void checkCollisions(GameObject& owner, Scene& scene);
	void checkCollisionsWith(GameObject& owner, Scene& scene, GameObject::Type objType);
	void callOnCollision(GameObject& owner, GameObject& other, Scene& scene);
	void correctPosition(GameObject& owner, GameObject& other, Scene& scene, Axis axis);

};

#endif //PHYSICSCOMPONENT_H