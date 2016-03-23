#include "PhysicsComponent.h"

#include "Components/Collider/ColliderComponent.h"
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
	updatePosition(owner_, scene, Axis::X);
	updatePosition(owner_, scene, Axis::Y);

	if (collider_)
	{
		checkCollisions(owner_, scene);
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

void PhysicsComponent::updatePosition(GameObject& owner, Scene& scene, Axis axis)
{
	switch (axis)
	{
		case Axis::X:
			velX_ += accelX_ * Time::getElapsedUpdateTimeSeconds();
			owner.setPosX(owner.getPosX() + velX_ * Time::getElapsedUpdateTimeSeconds());
			break;
		case Axis::Y:
			enactGravity();
			velY_ += accelY_ * Time::getElapsedUpdateTimeSeconds();
			owner.setPosY(owner.getPosY() + velY_ * Time::getElapsedUpdateTimeSeconds());
			break;
		default:
			break;
	}
	
	if (collider_)
	{
		correctPositionAfterCollision(owner, scene, axis);
	}

}

void PhysicsComponent::correctPositionAfterCollision(GameObject& owner, Scene& scene, Axis axis)
{
	if (owner.getType() != GameObject::Type::TILE)
	{
		int startC = std::max(0, (int) (owner.getPosX() / Constants::TILE_SIZE));
		int startR = std::max(0, (int) (owner.getPosY() / Constants::TILE_SIZE));
		int endC = std::min(scene.gameObjects.getTiles().cols - 1, (int)((owner.getPosX() + collider_->getWidth()) / Constants::TILE_SIZE));
		int endR = std::min(scene.gameObjects.getTiles().rows - 1, (int)((owner.getPosY() + collider_->getHeight()) / Constants::TILE_SIZE));


		for (int c = startC; c <= endC; ++c)
		{
			for(int r = startR; r <= endR; ++r)
			{
				GameObject& tile = scene.gameObjects.getTiles().tiles[r][c];

				if (collider_->checkCollision(tile))
				{
					correctPosition(owner, tile, scene, axis);
					callOnCollision(owner, tile, scene);
				}
			}
		}
	}
}

void PhysicsComponent::checkCollisions(GameObject& owner, Scene& scene)
{
	if (owner.getType() == GameObject::Type::PLAYER || owner.getType() == GameObject::Type::PLAYER_PROJECTILE)
	{
		for (auto& enemy : scene.gameObjects.get(GameObject::Type::ENEMY))
		{
			auto& object = *enemy;
			if (collider_->checkCollision(object))
			{
				callOnCollision(owner, object, scene);
			}
		}
	}

	if (owner.getType() == GameObject::Type::PLAYER)
	{
		for (auto& pickup : scene.gameObjects.get(GameObject::Type::DROP))
		{
			auto& object = *pickup;
			if (collider_->checkCollision(object))
			{
				callOnCollision(owner, object, scene);
			}
		}
	}
}

void PhysicsComponent::callOnCollision(GameObject& owner, GameObject& other, Scene& scene)
{
	ColliderComponent* otherCollider = other.getComponent<ColliderComponent>(); 
	owner.broadcastEvent(CollisionEvent(scene, other, *otherCollider));
	other.broadcastEvent(CollisionEvent(scene, owner, *collider_));
}

void PhysicsComponent::correctPosition(GameObject& owner, GameObject& other, Scene& scene, Axis axis)
{
	ColliderComponent* otherCollider = other.getComponent<ColliderComponent>();
	switch(axis)
	{
		case Axis::X:
			if (isMovingLeft())
			{
				owner.setPosX(otherCollider->getRight() - collider_->getOffsetX());
			}
			else
			{
				owner.setPosX(otherCollider->getLeft() - collider_->getWidth() - collider_->getOffsetX());
			}
			setVelX(0.0f);
			break;

		case Axis::Y:
			if (isMovingUp())
			{
				owner.setPosY(otherCollider->getBottom() - collider_->getOffsetY());
			}
			else
			{
				owner.setPosY(otherCollider->getTop() - collider_->getHeight() - collider_->getOffsetY());
				falling_ = false;
			}
			setVelY(0.0f);
			break;
		default:
			break;
	}
}

