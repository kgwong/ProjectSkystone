#include "Player.h"


Player::Player(GameWindow* gw)
	:animation(gw, "playerAnimation.png", 4, 30, 60, 4, 1)
{
	width = animation.getWidth();
	height = animation.getHeight();

	test = loadTexture(gw->renderer, "testTile.png");
}


Player::~Player()
{
}

void Player::handleInput2()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	if(keyStates[SDL_SCANCODE_LEFT])
	{
		velX = -5;
		falling = true;
	}
	else if(keyStates[SDL_SCANCODE_RIGHT])
	{
		velX = 5;
		falling = true;
	}
	else
		velX = 0;

}

void Player::handleInput(SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
		case SDLK_a:
			std::cout << "a pressed" << std::endl;
			jump();
			break;
		case SDLK_s:
			std::cout << "S pressed" << std::endl;
			shoot();
			break;
		/*
		case SDLK_LEFT:
			velX = -5;
			break;
		case SDLK_RIGHT:
			velX = 5;
			break;*/
		default:
			break;
	}
}

void Player::draw()
{
	animation.renderFrame(position.x, position.y);
}

void Player::update(Level& level)
{
	moveX();

	for (auto e = level.enemies.begin(); e < level.enemies.end(); ++e)
	{
		if (checkCollision(*e))
			handleCollisionX(*e);
	}

	int sz = level.getTileSize();
	int minX = position.x;
	int maxX = position.x + width;

	int minY = position.y;
	int maxY = position.y + height;

	for (int x = minX/sz; x <= maxX/sz; ++x)
	{
		for(int y = minY/sz; y <= maxY/sz; ++y)
		{
			level.tileArrangement[y][x].changeImage(test);
			Tile& tile = level.tileArrangement[y][x];
			if(tile.tileType == 1 && checkCollision(tile))
			{
				handleCollisionX(tile);
			}
		}
	}

	moveY();

	for (auto e = level.enemies.begin(); e < level.enemies.end(); ++e)
	{
		if (checkCollision(*e))
			handleCollisionY(*e); //double
	}


	for (int x = position.x/sz; x <= (position.x+width)/sz; ++x)
	{
		for(int y = position.y/sz; y <= (position.y+height)/sz; ++y)
		{
			level.tileArrangement[y][x].changeImage(test);
			Tile& tile = level.tileArrangement[y][x];
			if(tile.tileType == 1 && checkCollision(tile))
			{
				handleCollisionY(tile);
			}
		}
	}


}

void Player::jump()
{
	if (!falling)
	{
		velY = JUMP_VELOCITY;
		falling = true;
	}
}

void Player::shoot()
{
	std::cout << "SHOOTING!! PEW PEW PEW" << std::endl;
}

void Player::handleCollisionX(CollidingObject& other)
{
	if (isMovingLeft())
		position.x = other.getPosX() + other.getWidth();
	else //isMovingRight
		position.x = other.getPosX() - width;

	velX = 0;

}

void Player::handleCollisionY(CollidingObject& other)
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