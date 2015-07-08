#include "Enemy.h"


Enemy::Enemy(GameWindow* gw, Sprite* s)
	: _sprite(s)
{
	width = _sprite->getWidth();
	height = _sprite->getHeight();
}


Enemy::~Enemy()
{
}

void Enemy::update(LevelEntities& entities)
{
	PhysicalObject::moveX();
	for (auto i = entities.tiles.begin(); i < entities.tiles.end(); ++i)
	{
		for (auto j = i->begin(); j < i->end(); ++j)
		{
			Tile& t = *j;
			if (t.tileType == 1 && checkCollision(t))
			{
				handleCollisionX(t);
			}
		}
	}

	PhysicalObject::moveY();

	for (auto i = entities.tiles.begin(); i < entities.tiles.end(); ++i)
	{
		for (auto j = i->begin(); j < i->end(); ++j)
		{
			Tile& t = *j;
			if (t.tileType == 1 && checkCollision(t))
			{
				handleCollisionY(t);
			}
		}
	}
}

void Enemy::render()
{
	_sprite->render(position.x, position.y);
}

void Enemy::handleCollisionX(CollidingObject& other)
{
	if (isMovingLeft())
		position.x = other.getPosX() + other.getWidth();
	else //isMovingRight
		position.x = other.getPosX() - width;
}


void Enemy::handleCollisionY(CollidingObject& other)
{
	if (isMovingUp())
		position.y = other.getPosY() + other.getHeight();
	else //isMovingDown
	{
		position.y = other.getPosY() - height;
		falling = false;
	}
}