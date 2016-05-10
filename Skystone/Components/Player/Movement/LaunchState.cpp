#include "LaunchState.h"

#include "PlayerMovementState.h"
#include "GameObject/GameObject.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"

LaunchState::LaunchState(GameObject& owner)
	:PlayerState(owner)
{
	someSwitch_ = true;
	speed_ = 0.0f;
}

LaunchState::~LaunchState()
{
}

void LaunchState::onEnter(Scene& scene)
{
	someSwitch_ = true;
	//hack -- Kevin
	direction_ = 0;
	direction_ = owner_.getComponent<PlayerControlComponent>()->MovementState().direction;
	speed_ = owner_.getComponent<PlayerControlComponent>()->MovementState().speed;
	angle_ = owner_.getComponent<PlayerControlComponent>()->MovementState().angle;
	radius_ = owner_.getComponent<PlayerControlComponent>()->MovementState().radius;
	//LOG("HARVEY") << "direction: " << direction_;
	LOG("HARVEY") << "SPEED: " << speed_;
	
	//SCALING needs to be based on how long the rope is. ~ lookup momentum from releasing rope.
	auto physics = owner_.getComponent<PhysicsComponent>();
	angle_ = toRadians(angle_);
	float xVelocity = radius_ / cosf(angle_) * direction_;
	if (angle_ <= 0)
		angle_ = -angle_;
	float yVelocity = sqrtf((physics->GRAVITY * radius_) / sinf(2 * angle_)) * -1;
	float multiplier = 2.67f;
	LOG("HARVEY") << "DIRECTION: " << direction_;
	LOG("HARVEY") << "XVELOCITY: " << xVelocity;
	LOG("HARVEY") << "YVELOCITY: " << yVelocity;
	LOG("HARVEY") << "radius: " << radius_;
	LOG("HARVEY") << "angle_: " << angle_;
	owner_.getComponent<PhysicsComponent>()->setVelX(xVelocity * multiplier);
	owner_.getComponent<PhysicsComponent>()->setVelY(yVelocity * multiplier);
	
	//x-velocity = rope length / (cos(theta) * time);
	//assume time = 1;
	//y-velocity = sqrt ( (rope length * gravity) / sin(2 * theta) )
	//theta = is the angle of the player relative to its pivot.
	//http://datagenetics.com/blog/september42014/index.html
}

void LaunchState::onExit(Scene& scene)
{
	speed_ = 0.0f;
	owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(0);
}

void LaunchState::handleInput(Scene& scene, SDL_Event& e)
{

}

void LaunchState::update(Scene& scene)
{

	if (!someSwitch_)
	{
		auto playerPhysics = owner_.getComponent<PhysicsComponent>();
		playerPhysics->enableGravity(true);
		if (!owner_.getComponent<PhysicsComponent>()->isFalling())
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		}
	}
	else
	{
		someSwitch_ = false;
	}
}

void LaunchState::setSpeed(float s)
{
	speed_ = s;
}
