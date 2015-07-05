#include "PlayerProjectile.h"


PlayerProjectile::PlayerProjectile(Point position, int vel, Animation* animation, Direction dir)
	:_animation(animation)
{
	toggleGravity(false);
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

void PlayerProjectile::update()
{
	moveX();
	moveY();
}

void PlayerProjectile::draw()
{
	_animation->renderFrame(position.x, position.y);
}
