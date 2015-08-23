#include "PhysicsComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "GameConstants.h"
#include "CollisionInfo.h"

#include <algorithm>

PhysicsComponent::PhysicsComponent()
	:_velX(0), _velY(0),
	_accelX(0), _accelY(0),
	_gravityEnabled(true), _falling(true)
{
}

PhysicsComponent::~PhysicsComponent()
{
}


void PhysicsComponent::update(GameObject& owner, Level& level, ColliderComponent* collider)
{
	updatePosition(owner, Axis::X);
	updatePositionAfterCollision(owner, level, collider, Axis::X);

	updatePosition(owner, Axis::Y);
	updatePositionAfterCollision(owner, level, collider, Axis::Y);
}

void PhysicsComponent::enableGravity(bool gravity)
{
	_gravityEnabled = gravity;
}

void PhysicsComponent::enactGravity()
{
	if (_gravityEnabled)
	{
		_velY += GRAVITY;
		if (_velY > TERMINAL_VELOCITY)
			_velY = TERMINAL_VELOCITY;
	}

	_falling = true;
}

void PhysicsComponent::setVelX(int velX)
{
	_velX = velX;
}

void PhysicsComponent::setVelY(int velY)
{
	_velY = velY;
}

void PhysicsComponent::setAccelX(int accelX)
{
	_accelX = accelX;
}

void PhysicsComponent::setAccelY(int accelY)
{
	_accelY = accelY;		
}


int PhysicsComponent::getVelX() const
{
	return _velX;
}

int PhysicsComponent::getVelY() const
{
	return _velY;
}

int PhysicsComponent::getAccelX() const
{
	return _accelX;
}

int PhysicsComponent::getAccelY() const
{
	return _accelY;		
}

bool PhysicsComponent::isMovingUp() const
{
	return _velY < 0;
}

bool PhysicsComponent::isMovingDown() const
{
	return _velY > 0;
}

bool PhysicsComponent::isMovingLeft() const
{
	return _velX < 0;
}

bool PhysicsComponent::isMovingRight() const
{
	return _velX > 0;
}

bool PhysicsComponent::isFalling() const
{
	return _falling;
}

void PhysicsComponent::updatePosition(GameObject& owner, Axis axis)
{
	switch(axis)
	{
		case Axis::X:
			_velX += _accelX; 
			owner.setPosX(owner.getPosX() + _velX);
			break;
		case Axis::Y:
			enactGravity();
			_velY += _accelY; 
			owner.setPosY(owner.getPosY() + _velY);
			break;
		default:
			break;
	}
}

void PhysicsComponent::updatePositionAfterCollision(GameObject& owner, Level& level, ColliderComponent* collider, Axis axis)
{
	if (collider)
	{
		collider->update(owner);

		if (owner.getType() != EntityType::ENVIRONMENT)
		{
			int startC = std::max(0, owner.getPosX() / Constants::TILE_SIZE);
			int startR = std::max(0, owner.getPosY() / Constants::TILE_SIZE);
			int endC = std::min(level.tileArrangement.cols - 1, (owner.getPosX() + collider->getWidth()) / Constants::TILE_SIZE);
			int endR = std::min(level.tileArrangement.rows - 1, (owner.getPosY() + collider->getHeight()) / Constants::TILE_SIZE);

			for (int c = startC; c <= endC; ++c)
			{
				for(int r = startR; r <= endR; ++r)
				{						
					Tile& tile = level.tileArrangement.tiles[r][c];

					if (collider->checkCollision(tile))
						handleCollision(owner, tile, level, collider, axis);
				}
			}
		}

		if (owner.getType() == EntityType::PLAYER || owner.getType() == EntityType::PLAYER_PROJECTILE )
		{
			for (auto& enemy : level.enemies)
				if (collider->checkCollision(enemy))
					handleCollision(owner, enemy, level, collider, axis);
		}

		if (owner.getType() == EntityType::PLAYER) //only player has collision with pickups 
		{
			for (auto& pickup : level.pickups)
				if (collider->checkCollision(pickup))
					handleCollision(owner, pickup, level, collider, axis); //make this a non-physical collision!
		}
	}

}

void PhysicsComponent::handleCollision(GameObject& owner, GameObject& other, Level& level, ColliderComponent* collider, Axis axis)
{
	//
	//ColliderComponent* otherCollider = static_cast<ColliderComponent*>(other.getComponent(ComponentType::COLLIDER));
	ColliderComponent* otherCollider = other.getComponent<ColliderComponent>();
	switch(axis)
	{
		case Axis::X:
			if (isMovingLeft())
				owner.setPosX(otherCollider->getRight() - collider->getOffsetX());
			else //isMovingRight
				owner.setPosX(otherCollider->getLeft() - collider->getWidth() - collider->getOffsetX());
			setVelX(0);
			break;

		case Axis::Y:
			if (isMovingUp())
				owner.setPosY(otherCollider->getBottom() - collider->getOffsetY());
			else //isMovingDown
			{
				owner.setPosY(otherCollider->getTop() - collider->getHeight() - collider->getOffsetY());
				_falling = false;
			}
			setVelY(0);
			break;
		default:
			break;
	}
	collider->update(owner); 
	other.onCollision(CollisionInfo{level, owner, *otherCollider});
	owner.onCollision(CollisionInfo{level, other, *otherCollider});
}