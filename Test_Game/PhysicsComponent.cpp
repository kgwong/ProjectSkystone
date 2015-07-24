#include "PhysicsComponent.h"

#include "GameObject.h"
#include "LevelEntities.h"

PhysicsComponent::PhysicsComponent()
	:_velX(0), _velY(0),
	_accelX(0), _accelY(0),
	_gravityEnabled(true), _falling(true)
{
}


PhysicsComponent::~PhysicsComponent()
{
}


void PhysicsComponent::update(GameObject& owner, LevelEntities& entities, ColliderComponent* collider)
{
	updatePosition(owner, X_AXIS);

	if (collider)
	{
		collider->update(owner);

		if (owner.getType() != ENVIRONMENT) //environment collision
		{
			for (int x = owner.getPosX()/entities.tileSize; x <= (owner.getPosX()+owner.getWidth())/entities.tileSize; ++x)
			{
				for(int y = owner.getPosY()/entities.tileSize; y <= (owner.getPosY()+owner.getHeight())/entities.tileSize; ++y)
				{
					Tile& tile = entities.tiles[y][x];

					if(tile.tileType == 1 && tile._colliderComponent.checkCollision(*collider))
						handleCollision(owner, tile, collider, X_AXIS);
				}
			}
		}

		if (owner.getType() != ENEMY)
		{
			for (auto enemyIter = entities.enemies.begin(); enemyIter < entities.enemies.end(); ++enemyIter)
			{
				if(enemyIter->_colliderComponent.checkCollision(*collider))
					handleCollision(owner, *enemyIter, collider, X_AXIS);
			}
		}
	}

	updatePosition(owner, Y_AXIS);

	if (collider)
	{
		collider->update(owner); 

		if (owner.getType() != ENVIRONMENT) //environment collision
		{
			for (int x = owner.getPosX()/entities.tileSize; x <= (owner.getPosX() + owner.getWidth())/entities.tileSize; ++x)
			{
				for(int y = owner.getPosY()/entities.tileSize; y <= (owner.getPosY() + owner.getHeight())/entities.tileSize; ++y)
				{
					Tile& tile = entities.tiles[y][x];
					if(tile.tileType == 1 && tile._colliderComponent.checkCollision(*collider))
						handleCollision(owner, tile, collider, Y_AXIS);
				}
			}
		}

		if (owner.getType() != ENEMY)
		{
			for (auto enemyIter = entities.enemies.begin(); enemyIter < entities.enemies.end(); ++enemyIter)
			{
				if(enemyIter->_colliderComponent.checkCollision(*collider))
					handleCollision(owner, *enemyIter, collider, Y_AXIS);
			}
		}
	}
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


int PhysicsComponent::getVelX()
{
	return _velX;
}

int PhysicsComponent::getVelY()
{
	return _velY;
}

int PhysicsComponent::getAccelX()
{
	return _accelX;
}

int PhysicsComponent::getAccelY()
{
	return _accelY;		
}

bool PhysicsComponent::isMovingUp()
{
	return _velY < 0;
}

bool PhysicsComponent::isMovingDown()
{
	return _velY > 0;
}

bool PhysicsComponent::isMovingLeft()
{
	return _velX < 0;
}

bool PhysicsComponent::isMovingRight()
{
	return _velX > 0;
}

bool PhysicsComponent::isFalling()
{
	return _falling;
}

void PhysicsComponent::updatePosition(GameObject& owner, Axis axis)
{
	switch(axis)
	{
		case X_AXIS:
			_velX += _accelX; 
			owner.setPosX(owner.getPosX() + _velX);
			break;
		case Y_AXIS:
			enactGravity();
			_velY += _accelY; 
			owner.setPosY(owner.getPosY() + _velY);
			break;
		default:
			break;
	}
}

void PhysicsComponent::handleCollision(GameObject& owner, GameObject& other, ColliderComponent* collider, Axis axis)
{
	switch(axis)
	{
		case X_AXIS:
			if (isMovingLeft())
				owner.setPosX(other.getPosX() + other.getWidth());
			else //isMovingRight
				owner.setPosX(other.getPosX() - owner.getWidth());
			setVelX(0);
			break;

		case Y_AXIS:
			if (isMovingUp())
				owner.setPosY(other.getPosY() + other.getHeight());
			else //isMovingDown
			{
				owner.setPosY(other.getPosY() - owner.getHeight());
				_falling = false;
			}
			setVelY(0);
			break;
		default:
			break;
	}
	collider->update(owner); 
	other.onCollision(owner);
	owner.onCollision(other);
}