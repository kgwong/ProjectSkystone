#include "FallingAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Common/StickOnCollision.h"
#include "GameTypes/Point.h"

const float FallingAIComponent::DEFAULT_Y_VELOCITY = 0 * 60.0f;
const float FallingAIComponent::DEFAULT_RISE_VELOCITY = -3 * 60.0f;
const float FallingAIComponent::DEFAULT_X_RADIUS = 25;
const float FallingAIComponent::DEFAULT_Y_RADIUS = 100;

FallingAIComponent::FallingAIComponent(GameObject& owner)
	: AIComponent(owner), 
	yVelocity_(DEFAULT_Y_VELOCITY),
	xRadius_(DEFAULT_X_RADIUS),
	yRadius_(DEFAULT_Y_RADIUS),
	timer_(0),
	isFalling_(false)
{
	state = STATE::NEUTRAL;
}

FallingAIComponent::~FallingAIComponent()
{
}


void FallingAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	xRadius_ = owner_.getComponent<ColliderComponent>()->getWidth();
	yRadius_ = owner_.getComponent<ColliderComponent>()->getHeight();
	state = STATE::NEUTRAL;

}


void FallingAIComponent::update(Scene& scene)
{
	float dist = Point::getDistance(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
	float yDist = Point::getYDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
	float xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());

	//new way to calculate
	Point upperLeftCorner = owner_.getPos();
	Point upperRightCorner = owner_.getPos();
	Point playerPos = scene.gameObjects.getPlayer().getPos();
	upperRightCorner.x += xRadius_;

	//colliders
	auto sticky = owner_.getComponent<StickOnCollision>();

	//enum states
	//1. falling   pos yvelocity
	//2. rising    neg yvelocity
	//3. neutral - 0 yvelocity, if mob has collided with the bottom edge of a tile.


	if (sticky->isConnected)
	{
		state = STATE::NEUTRAL;
	}
	else if (upperLeftCorner.x < playerPos.x && upperRightCorner.x > playerPos.x)
	{
		state = STATE::FALLING;
	}
	else
	{
		state = STATE::RISING;
	}

	
	if (state == STATE::NEUTRAL)
	{
		physics_->setVelY(0);
		physics_->enableGravity(false);
	}

	if (state == STATE::FALLING)
	{
		physics_->enableGravity(true);
		float yvel = physics_->getVelY();
		physics_->setVelY(yvel * 1.2);
	}

	if (state == STATE::RISING)
	{
		physics_->enableGravity(false);
		physics_->setVelY(DEFAULT_RISE_VELOCITY);
	}







	//if (!isFalling_)
	//{
	//	physics_->enableGravity(false);
	//	yVelocity_ = DEFAULT_RISE_VELOCITY;
	//	physics_->setVelY(yVelocity_);
	//}
	//else//if falling
	//{
	//	timer_++;
	//	timer_ = timer_ % DEFAULT_TIME_INTERVAL;
	//}


	//if (timer_ == 0)
	//	isFalling_ = false;	
	
	//if (!isFalling_ && playerPos.x > upperLeftCorner.x && playerPos.x < upperRightCorner.x)
	//{
	//	physics_->enableGravity(true);
	//	float velY = physics_->getVelY();
	//	physics_->setVelY(velY * 1.2);
	//	isFalling_ = true;
	//}


}

