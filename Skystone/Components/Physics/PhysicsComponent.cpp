#include "PhysicsComponent.h"

#include "Components/Collider/ColliderComponent.h"
#include "ComponentEvents/CollisionEvent.h"
#include "Game/GameConstants.h"
#include "Game/GameTime.h"
#include "Application/Log.h"

#include <algorithm>

const float PhysicsComponent::GRAVITY = 60.0f;
const float PhysicsComponent::TERMINAL_VELOCITY = 1200.0f;

PhysicsComponent::PhysicsComponent(GameObject& owner)
	: Component(owner),
	velX_(0), velY_(0),
	accelX_(0), accelY_(0),
	gravityEnabled_(true), falling_(true),
	collider_(nullptr)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::start(Scene& scene)
{
	collider_ = owner_.getComponent<ColliderComponent>();
}

void PhysicsComponent::update(Scene& scene)
{
	updatePosition(scene, Axis::X);
	updatePosition(scene, Axis::Y);

	if (collider_)
	{
		checkCollisions(scene);
	}
}

Component::Type PhysicsComponent::getType()
{
	return Component::Type::PHYSICS;
}

void PhysicsComponent::enableGravity(bool gravity)
{
	gravityEnabled_ = gravity;
}

bool PhysicsComponent::gravityEnabled()
{
	return gravityEnabled_;
}

void PhysicsComponent::enactGravity()
{
	if (gravityEnabled_)
	{
		velY_ += GRAVITY * Time::getElapsedUpdateTimeSeconds() * 60;
		if (velY_ > TERMINAL_VELOCITY)
		{
			velY_ = TERMINAL_VELOCITY;
		}
	}

	falling_ = true;
}

void PhysicsComponent::setVelX(float velX)
{
	velX_ = velX;
}

void PhysicsComponent::setVelY(float velY)
{
	velY_ = velY;
}

void PhysicsComponent::setAccelX(float accelX)
{
	accelX_ = accelX;
}

void PhysicsComponent::setAccelY(float accelY)
{
	accelY_ = accelY;
}

float PhysicsComponent::getVelX() const
{
	return velX_;
}

float PhysicsComponent::getVelY() const
{
	return velY_;
}

float PhysicsComponent::getAccelX() const
{
	return accelX_;
}

float PhysicsComponent::getAccelY() const
{
	return accelY_;
}

bool PhysicsComponent::isMovingUp() const
{
	return velY_ < 0;
}

bool PhysicsComponent::isMovingDown() const
{
	return velY_ > 0;
}

bool PhysicsComponent::isMovingLeft() const
{
	return velX_ < 0;
}

bool PhysicsComponent::isMovingRight() const
{
	return velX_ > 0;
}

bool PhysicsComponent::isFalling() const
{
	return falling_;
}

void PhysicsComponent::updatePosition(Scene& scene, Axis axis)
{
	switch (axis)
	{
		case Axis::X:
			velX_ += accelX_ * Time::getElapsedUpdateTimeSeconds();
			owner_.setPosX(owner_.getPosX() + velX_ * Time::getElapsedUpdateTimeSeconds());
			break;
		case Axis::Y:
			enactGravity();
			velY_ += accelY_ * Time::getElapsedUpdateTimeSeconds();
			owner_.setPosY(owner_.getPosY() + velY_ * Time::getElapsedUpdateTimeSeconds());
			break;
		default:
			break;
	}
	
	if (collider_)
	{
		correctPositionAfterCollision(scene, axis);
	}
}

void PhysicsComponent::correctPositionAfterCollision(Scene& scene, Axis axis)
{
	if (owner_.getType() != GameObject::Type::TILE)
	{
		int startC = std::max(0, (int) (owner_.getPosX() / Constants::TILE_SIZE));
		int startR = std::max(0, (int) (owner_.getPosY() / Constants::TILE_SIZE));
		int endC = std::min(scene.gameObjects.getTiles().cols - 1, (int)((owner_.getPosX() + collider_->getWidth()) / Constants::TILE_SIZE));
		int endR = std::min(scene.gameObjects.getTiles().rows - 1, (int)((owner_.getPosY() + collider_->getHeight()) / Constants::TILE_SIZE));


		for (int c = startC; c <= endC; ++c)
		{
			for(int r = startR; r <= endR; ++r)
			{
				GameObject& tile = scene.gameObjects.getTiles().tiles[r][c];

				if (collider_->checkCollision(tile))
				{
					correctPosition(tile, scene, axis);
					callOnCollision(tile, scene);
				}
			}
		}
	}
}

void PhysicsComponent::checkCollisions(Scene& scene)
{
	if (owner_.getType() == GameObject::Type::PLAYER || owner_.getType() == GameObject::Type::PLAYER_PROJECTILE)
	{
		checkCollisionsWith(scene, GameObject::Type::ENEMY);
	}

	if (owner_.getType() == GameObject::Type::PLAYER)
	{
		checkCollisionsWith(scene, GameObject::Type::DROP);
		checkCollisionsWith(scene, GameObject::Type::ENEMY_PROJECTILE);
	}
}

void PhysicsComponent::checkCollisionsWith(Scene& scene, GameObject::Type objType)
{
	for (auto& objPtr : scene.gameObjects.get(objType))
	{
		auto& object = *objPtr;
		if (collider_->checkCollision(object))
		{
			callOnCollision(object, scene);
		}
	}
}

void PhysicsComponent::callOnCollision(GameObject& other, Scene& scene)
{
	ColliderComponent* otherCollider = other.getComponent<ColliderComponent>(); 
	owner_.broadcastEvent(CollisionEvent(scene, other, *otherCollider));
	other.broadcastEvent(CollisionEvent(scene, owner_, *collider_));
}

void PhysicsComponent::correctPosition(GameObject& other, Scene& scene, Axis axis)
{
	ColliderComponent* otherCollider = other.getComponent<ColliderComponent>();
	switch(axis)
	{
		case Axis::X:
			if (isMovingLeft())
			{
				owner_.setPosX(otherCollider->getRight() - collider_->getOffsetX());
			}
			else
			{
				owner_.setPosX(otherCollider->getLeft() - collider_->getWidth() - collider_->getOffsetX());
			}
			setVelX(0.0f);
			break;

		case Axis::Y:
			if (isMovingUp())
			{
				owner_.setPosY(otherCollider->getBottom() - collider_->getOffsetY());
			}
			else
			{
				owner_.setPosY(otherCollider->getTop() - collider_->getHeight() - collider_->getOffsetY());
				falling_ = false;
			}
			setVelY(0.0f);
			break;
		default:
			break;
	}
}

