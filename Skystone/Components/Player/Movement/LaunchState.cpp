#include "LaunchState.h"

#include "PlayerMovementState.h"
#include "GameObject/GameObject.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"
#include "Game/GameTime.h"


const float LaunchState::TERMINAL_VELOCITY = 2000.0f;

LaunchState::LaunchState(GameObject& owner)
	:PlayerState(owner)
{
	someSwitch_ = true;
	speed_ = 0.0f;
}

LaunchState::~LaunchState()
{
}

//my code is as ugly as Sam's poop
void LaunchState::onEnter(Scene& scene)
{
	someSwitch_ = true;
	//hack -- Kevin
	float xVel = owner_.getComponent<PlayerControlComponent>()->MovementState().xVelocity;
	direction_ = fabsf(xVel) / xVel;
	//owner_.getComponent<PlayerControlComponent>()->MovementState().direction;
	speed_ = owner_.getComponent<PlayerControlComponent>()->MovementState().speed;
	angle_ = owner_.getComponent<PlayerControlComponent>()->MovementState().angle;
	radius_ = owner_.getComponent<PlayerControlComponent>()->MovementState().radius;

	//SCALING needs to be based on how long the rope is. ~ lookup momentum from releasing rope.
	auto physics = owner_.getComponent<PhysicsComponent>();
	angle_ = toRadians(angle_);
	float xVelocity = 2 * (radius_ / cosf(angle_)) * direction_;

	float divisionbyZeroisDangerous = sinf(2 * M_PI * angle_);
	float yVelocity = 0;

	if (divisionbyZeroisDangerous == 0)
		yVelocity = TERMINAL_VELOCITY;
	else if (divisionbyZeroisDangerous < 0)
	{
		divisionbyZeroisDangerous *= -1;
		yVelocity = sqrtf((physics->GRAVITY * radius_) / divisionbyZeroisDangerous) * -1;
	}
	else
		yVelocity = sqrtf((physics->GRAVITY * radius_) / divisionbyZeroisDangerous) * -1;

	float xmultiplier = 10.24f;
	float ymultiplier = 20.24f;

	//capping out velocities.
	//if (xVelocity > TERMINAL_VELOCITY)
	//	xVelocity = TERMINAL_VELOCITY;
	//if (xVelocity < -TERMINAL_VELOCITY)
	//	xVelocity = -TERMINAL_VELOCITY;
	//if (yVelocity > TERMINAL_VELOCITY)
	//	yVelocity = TERMINAL_VELOCITY;
	//if (yVelocity < -TERMINAL_VELOCITY)
	//	yVelocity = -TERMINAL_VELOCITY;
	Point projectedPosition = owner_.getPos();
	projectedPosition.x += xVelocity * direction_ * xmultiplier;
	projectedPosition.y += yVelocity * ymultiplier;

	if (projectedPosition.inBounds(scene.getWidth(), scene.getHeight()))
	{
		//comment this out for fast launches.
		owner_.getComponent<PhysicsComponent>()->setVelX(xVelocity * direction_ * xmultiplier * Time::getElapsedUpdateTime());
		owner_.getComponent<PhysicsComponent>()->setVelY(yVelocity * ymultiplier * Time::getElapsedUpdateTime());
		
		//comment this out for smooth launches.
		//owner_.getComponent<PhysicsComponent>()->setAccelX(xVelocity * direction_ * xmultiplier);
		//owner_.getComponent<PhysicsComponent>()->setAccelY(yVelocity * ymultiplier);
	}
	
	//x-velocity = rope length / (cos(theta) * time);
	//assume time = 1;
	//y-velocity = sqrt ( (rope length * gravity) / sin(2 * theta) )
	//theta = is the angle of the player relative to its pivot.
	//http://datagenetics.com/blog/september42014/index.html

	LOG("HARVEY") << "DIRECTION: " << direction_;
	LOG("HARVEY") << "XVELOCITY: " << xVelocity;
	LOG("HARVEY") << "YVELOCITY: " << yVelocity;
	LOG("HARVEY") << "radius: " << radius_;
	LOG("HARVEY") << "angle_: " << angle_;
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
