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

}

void Enemy::render()
{
	_sprite->render(position.x, position.y);
}
