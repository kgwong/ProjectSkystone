#include "PlayerProjectile.h"


PlayerProjectile::PlayerProjectile(Point position, int vel, Animation* animation, Direction dir)
	:_active(true), _animation(animation)
{
	toggleGravity(false);

	width = _animation->getWidth();
	height = _animation->getHeight();

	this->position = position; 

	switch (dir)
	{
		case UP: velY = -vel; break;
		case DOWN: velY = vel; break;
		case LEFT: velX = -vel; break;
		case RIGHT: velX = vel; break;
		default: break;
	}
}


PlayerProjectile::~PlayerProjectile()
{
}

bool PlayerProjectile::isActive()
{
	return _active;
}

void PlayerProjectile::update(LevelEntities& entities)
{
	moveX();
	//lots of repeated code!!!

	for (auto i = entities.enemies.begin(); i < entities.enemies.end(); ++i)
	{
		if (checkCollision(*i))
		{
			handleCollisionX(*i);
			i->takeDamage(damage);
			_active = false;
		}	
	}

	for (int x = position.x/entities.tileSize; x <= (position.x + width)/entities.tileSize; ++x)
	{
		for(int y = position.y/entities.tileSize; y <= (position.y + height)/entities.tileSize; ++y)
		{
			Tile& tile = entities.tiles[y][x];
			if(tile.tileType == 1 && checkCollision(tile))
			{
				handleCollisionX(tile);
				_active = false;
			}
		}
	}
	moveY();

	for (int x = position.x/entities.tileSize; x <= (position.x + width)/entities.tileSize; ++x)
	{
		for(int y = position.y/entities.tileSize; y <= (position.y + height)/entities.tileSize; ++y)
		{
			Tile& tile = entities.tiles[y][x];
			if(tile.tileType == 1 && checkCollision(tile))
			{
				handleCollisionY(tile);
				_active = false;
			}
		}
	}

	for (auto i = entities.enemies.begin(); i < entities.enemies.end(); ++i)
	{
		if (checkCollision(*i))
		{
			handleCollisionY(*i);
			i->takeDamage(damage);
			_active = false;
		}	
	}

}

void PlayerProjectile::render()
{
	_animation->renderFrame(position.x, position.y);
}


void PlayerProjectile::handleCollisionX(CollidingObject& other)
{
	if (isMovingLeft())
		position.x = other.getPosX() + other.getWidth();
	else //isMovingRight
		position.x = other.getPosX() - width;

	velX = 0;

}

void PlayerProjectile::handleCollisionY(CollidingObject& other)
{
	if (isMovingUp())
		position.y = other.getPosY() + other.getHeight();
	else //isMovingDown
	{
		position.y = other.getPosY() - height;
		if (falling) 
			falling = false;
	}

	velY = 0;
}