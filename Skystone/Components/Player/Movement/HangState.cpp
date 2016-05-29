#include "HangState.h"
#include "Components/Player/Attack/PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"
#include "Game/GameTime.h"
#include "LaunchState.h"
#include "Components/Player/Attack/Aim/AimState.h"
#include "Components/Tile/TileComponent.h"
#include "Game/GameConstants.h"

//CONSTANTS
const float HangState::MAX_ANGLE = 80.0f;
const float HangState::DEFAULT_SPEED = 4.24f;
const float HangState::MAX_SPEED = 10.24f;
const float HangState::MIN_ROPE_LENGTH = 10.0f;
const float HangState::MAX_ROPE_LENGTH = 75.0f;

HangState::HangState(GameObject& owner)
	:PlayerState(owner)
{
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	ropeLength_ = 0.0f;
	ySpeed_ = 0.0f;
	yDirection_ = 0;
}

HangState::~HangState()
{
}


void HangState::onEnter(Scene& scene)
{
	LOG("HARVEY") << "HELLO";
	if (scene.gameObjects.playerHook == nullptr)
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		return;
	}
	if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookDisconnectState")
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		return;
	}
	//CANNOT change physics here....must do in update.
	hookPosition_ = scene.gameObjects.playerHook->getPos();
	hangPosition_ = owner_.getPos();
	ropeLength_ = owner_.getPosY() - hookPosition_.y;
	owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(0);
	ySpeed_ = DEFAULT_SPEED;
	yDirection_ = 0;


	//length of each rope segment is 2 pixels
	//total number of rope segments to be drawn = ropeLength_ / 2
	//int ropeSegCount = (int)(ropeLength_ - hookPosition_.y) / 2;

	////draw rope segments
	//for (int i = 0;i < ropeSegCount; ++i)
	//{
	//	Point segmentPos = owner_.getPos();
	//	segmentPos.x += scene.gameObjects.playerHook->getComponent<ColliderComponent>()->getWidth() / 2;
	//	//	segmentPos.y = segmentPos.y - (owner_.getComponent<ColliderComponent>()->getHeight() / 6);
	//	segmentPos.y -= i * 2;
	//	scene.gameObjects.add("RopeSegment", "rope Segment", segmentPos);
	//}


	//swing from a jumping start while launching the hook to the left or right.

	//1. calculate the xDistance from player to hook.
	//2. divide by absolute value of xDistance to obtain direction.
	float xdist = Point::getXDirection(hangPosition_, hookPosition_);
	int dir = 0;

	if(xdist != 0 && owner_.getComponent<PlayerControlComponent>()->MovementState().getPrevState()->name() != "SwingState")
		dir = (int)(xdist / fabsf(xdist));

	//if player is to the right of the hook, swing left
	if (dir > 0)
	{
		owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(-1);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "SwingState");
		return;
	}
	//if player is to the left of the hook, swing right
	if (dir < 0)
	{
		owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(1);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "SwingState");
		return;
	}
	if(dir == 0)
	{
		hangPosition_.x = hookPosition_.x;
		float frow = hangPosition_.y / Constants::TILE_SIZE;
		float fcol = hangPosition_.x / Constants::TILE_SIZE;
		int row = (int)roundf(frow);
		int col = (int)roundf(fcol);
		if (row < 0 || row >= scene.gameObjects.getTiles().rows)
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			return;
		}

		if (col < 0 || col >= scene.gameObjects.getTiles().cols)
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			return;
		}

		TileComponent::Type tileType = scene.gameObjects.getTiles().tiles[row][col].getComponent<TileComponent>()->getTileType();
		LOG("HARVEY") << "float row,col: " << frow << ", " << fcol;
		LOG("HARVEY") << "int row,col: " << row << ", " << col;
		//check if tile is in the way of where player will be put under when hanging.	
		if(tileType == TileComponent::Type::EMPTY)
			owner_.setPos(hangPosition_);
		else
		{
			LOG("HARVEY") << "CANNOT HANG... TILE IN THE WAY";
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		}
	}

	LOG("HARVEY") << "HOOK POSITION: " << hookPosition_;
	LOG("HARVEY") << "player position: " << owner_.getPos();
}
void HangState::onExit(Scene& scene)
{
	//reset everything
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	ropeLength_ = 0.0f;
	ySpeed_ = 0.0f;
	yDirection_ = 0;
	hangPosition_.x = 0.0f;
	hangPosition_.y = 0.0f;


}
void HangState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, ControlType::UP))
	{
		ySpeed_ += 0.65f;
		if (ySpeed_ > MAX_SPEED)
			ySpeed_ = MAX_SPEED;
		yDirection_ = -1;
	}
	else if (GameInputs::keyDown(e, ControlType::DOWN))
	{
		ySpeed_ += 0.65f;
		if (ySpeed_ > MAX_SPEED)
			ySpeed_ = MAX_SPEED;
		yDirection_ = 1;
	}
	else if (GameInputs::keyDown(e, ControlType::LEFT) || GameInputs::keyDown(e,ControlType::RIGHT))
	{
		if (GameInputs::keyDown(e, ControlType::LEFT))
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(-1);
		else
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(1);

		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "SwingState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(false);
	}
	else
		yDirection_ = 0;

}

void HangState::handleEvent(const CollisionEvent & e)
{
	if (e.getOtherObject().getType() == GameObject::Type::TILE)
	{
		LOG("HARVEY") << " I GOT HIT";
	}
}
void HangState::update(Scene& scene)
{
	if (owner_.getComponent<PlayerControlComponent>()->MovementState().direction == 0)
	{
		if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookLaunchState")
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		}
		else if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookDisconnectState")
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		}
		else
		{
			auto playerPhysics = owner_.getComponent<PhysicsComponent>();
			//if not turned off will build downward velocity
			playerPhysics->enableGravity(false);
			playerPhysics->setVelY(yDirection_ * ySpeed_ * Time::getElapsedUpdateTime());
			hangPosition_.y += ySpeed_ * yDirection_;
			ropeLength_ = owner_.getPosY() - hookPosition_.y;
		//	LOG("HARVEY") << "rope length: " << ropeLength_;
			//length of each rope segment is 2 pixels
			//total number of rope segments to be drawn = ropeLength_ / 2
			//ropeSegCount = (int)(ropeLength_ - hookPosition_.y) / 2;

			////draw rope segments
			//for (int i = 0;i < ropeSegCount; ++i)
			//{
			//	Point segmentPos = owner_.getPos();
			//	segmentPos.x += scene.gameObjects.playerHook->getComponent<ColliderComponent>()->getWidth() / 2;
			//	//	segmentPos.y = segmentPos.y - (owner_.getComponent<ColliderComponent>()->getHeight() / 6);
			//	segmentPos.y -= i * 2;
			//	scene.gameObjects.add("RopeSegment", "rope Segment", segmentPos);
			//}

			//add rope segments of going down the rope.
			//if (!scene.gameObjects.get(GameObject::Type::ROPE_SEGMENT).empty())
			//{
			//	if (yDirection_ > 0)
			//	{
			//		Point ropeSegPos = owner_.getPos();
			//		scene.gameObjects.add("RopeSegment", "Rope Segment", owner_.getPos());
			//	}
			//	//remove rope segments if going up the rope.
			//	if (yDirection_ < 0)
			//	{
			//		scene.gameObjects.get(GameObject::Type::ROPE_SEGMENT).erase(scene.gameObjects.get(GameObject::Type::ROPE_SEGMENT).begin());
			//	}
			//}
	/*		for (int i = 0;i < ropeSegCount; ++i)
			{
				scene.gameObjects.get(GameObject::Type::ROPE_SEGMENT).
			}*/


			if (MIN_ROPE_LENGTH >= ropeLength_)
			{
				ropeLength_ = MIN_ROPE_LENGTH;
				owner_.setPosY(owner_.getPosY() + MIN_ROPE_LENGTH);
			}

			//owner_.setPos(hangPosition_);
		}
	}
	
}



