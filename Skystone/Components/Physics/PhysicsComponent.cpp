#include "PhysicsComponent.h"

#include "Components/Collider/ColliderComponent.h"
#include "Game/GameConstants.h"

#include <algorithm>

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

void PhysicsComponent::start(Level& level)
{
	collider_ = owner_.getComponent<ColliderComponent>();
}

void PhysicsComponent::update(Level& level)
{
	updatePosition(owner_, level, Axis::X);
	updatePosition(owner_, level, Axis::Y);

	if (collider_)
	{
		checkCollisions(owner_, level);
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
		velY_ += GRAVITY;
		if (velY_ > TERMINAL_VELOCITY)
			velY_ = TERMINAL_VELOCITY;
	}

	falling_ = true;
}

void PhysicsComponent::setVelX(int velX)
{
	velX_ = velX;
}

void PhysicsComponent::setVelY(int velY)
{
	velY_ = velY;
}

void PhysicsComponent::setAccelX(int accelX)
{
	accelX_ = accelX;
}

void PhysicsComponent::setAccelY(int accelY)
{
	accelY_ = accelY;
}


int PhysicsComponent::getVelX() const
{
	return velX_;
}

int PhysicsComponent::getVelY() const
{
	return velY_;
}

int PhysicsComponent::getAccelX() const
{
	return accelX_;
}

int PhysicsComponent::getAccelY() const
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

void PhysicsComponent::updatePosition(GameObject& owner, Level& level, Axis axis)
{
	switch (axis)
	{
		case Axis::X:
			velX_ += accelX_;
			owner.setPosX(owner.getPosX() + velX_);
			break;
		case Axis::Y:
			enactGravity();
			velY_ += accelY_;
			owner.setPosY(owner.getPosY() + velY_);
			break;
		default:
			break;
	}
	
	if (collider_)
	{
		correctPositionAfterCollision(owner, level, axis);
	}

}

void PhysicsComponent::correctPositionAfterCollision(GameObject& owner, Level& level, Axis axis)
{
	if (owner.getType() != GameObject::Type::TILE)
	{
		int startC = std::max(0, owner.getPosX() / Constants::TILE_SIZE);
		int startR = std::max(0, owner.getPosY() / Constants::TILE_SIZE);
		int endC = std::min(level.tileArrangement.cols - 1, (owner.getPosX() + collider_->getWidth()) / Constants::TILE_SIZE);
		int endR = std::min(level.tileArrangement.rows - 1, (owner.getPosY() + collider_->getHeight()) / Constants::TILE_SIZE);

		for (int c = startC; c <= endC; ++c)
		{
			for(int r = startR; r <= endR; ++r)
			{
				GameObject& tile = level.tileArrangement.tiles[r][c];

				if (collider_->checkCollision(tile))
				{
					correctPosition(owner, tile, level, axis);
					callOnCollision(owner, tile, level);
				}
			}
		}
	}
}

void PhysicsComponent::checkCollisions(GameObject& owner, Level& level)
{
	if (owner.getType() == GameObject::Type::PLAYER || owner.getType() == GameObject::Type::PLAYER_PROJECTILE)
	{
		for (auto& enemy : level.enemies)
		{
			auto& object = *enemy;
			if (collider_->checkCollision(object))
			{
				callOnCollision(owner, object, level);
			}
		}
	}

	if (owner.getType() == GameObject::Type::PLAYER)
	{
		for (auto& pickup : level.drops)
		{
			auto& object = *pickup;
			if (collider_->checkCollision(object))
			{
				callOnCollision(owner, object, level);
			}
		}
	}
}

void PhysicsComponent::callOnCollision(GameObject& owner, GameObject& other, Level& level)
{
	ColliderComponent* otherCollider = other.getComponent<ColliderComponent>(); 
	owner.broadcastEvent(CollisionEvent(level, other, *otherCollider));
	other.broadcastEvent(CollisionEvent(level, owner, *collider_));
}

void PhysicsComponent::correctPosition(GameObject& owner, GameObject& other, Level& level, Axis axis)
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
			//setVelX(0);
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
			//setVelY(0);
			break;
		default:
			break;
	}
}

