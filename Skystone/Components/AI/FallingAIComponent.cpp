#include "FallingAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "GameTypes/Point.h"
#include "Application/Log.h"
#include "Game/GameTime.h"

const float FallingAIComponent::DEFAULT_Y_VELOCITY = 0 * 60.0f;
const float FallingAIComponent::DEFAULT_RISE_VELOCITY = -3 * 60.0f;

FallingAIComponent::FallingAIComponent(GameObject& owner)
	: AIComponent(owner)
{
}

FallingAIComponent::~FallingAIComponent()
{
}


void FallingAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	state_ = STATE::NEUTRAL;
	timer_ = 0;
}


void FallingAIComponent::update(Scene& scene)
{
	playerPos_ = scene.gameObjects.getPlayer().getPos();
	upperLeftCorner_ = owner_.getPos();
	upperRightCorner_ = owner_.getPos();
	upperRightCorner_.x += owner_.getComponent<ColliderComponent>()->getWidth();
	//enum states
	//1. falling   pos yvelocity
	//2. rising    neg yvelocity
	//3. neutral - 0 yvelocity, if mob has collided with the bottom edge of a tile.
	//4. delay

	if (state_ != STATE::RISING && state_ != STATE::DELAY && upperLeftCorner_.x < playerPos_.x && upperRightCorner_.x > playerPos_.x)
	{
		state_ = STATE::FALLING;
	}

	if (state_ == STATE::DELAY)
	{
		timer_ += 1;
		if (timer_ >= Time::getElapsedUpdateTime())
		{
			timer_ = 0.0f;
			state_ = STATE::NEUTRAL;
			LOG("HARVEY") << "NEUTRAL";
		}
	}
	if (state_ == STATE::NEUTRAL)
	{
		//LOG("HARVEY") << "BLOCK POSITION: " << owner_.getPos();
		physics_->enableGravity(false);
		physics_->setVelY(0);
	}
	else if (state_ == STATE::FALLING)
	{
		physics_->enableGravity(true);
		float yvel = physics_->getVelY();
		physics_->setVelY(yvel * 1.2);
	}

	if (state_ == STATE::RISING)
	{
		physics_->enableGravity(false);
		physics_->setVelY(DEFAULT_RISE_VELOCITY);
	}



}

void FallingAIComponent::handleEvent(const CollisionEvent & e)
{

	if (e.getOtherObject().getType() == GameObject::Type::TILE)
	{
		//colliders
		auto blockCollider = owner_.getComponent<ColliderComponent>();
		ColliderComponent& tileCollider = e.getOtherCollider();

		if (blockCollider->getBottom() == tileCollider.getTop())
		{
			state_ = STATE::RISING;
			LOG("HARVEY") << "RISING";
		}
		else if(state_ != STATE::NEUTRAL)
		{
			state_ = STATE::DELAY;
			LOG("HARVEY") << "DELAY";
		}


	}
}

