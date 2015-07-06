#include "Player.h"


Player::Player(GameWindow* gw)
	:dir(RIGHT), animation(gw, "playerAnimation.png", 4, 30, 60, 4, 1), 
	projectileAnimation(gw, "playerProjectile.png", 2, 20, 10, 2, 1),
	_shoot(false)
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
		dir = LEFT;
	}
	else if(keyStates[SDL_SCANCODE_RIGHT])
	{
		velX = 5;
		falling = true;
		dir = RIGHT;
	}
	else if (keyStates[SDL_SCANCODE_UP])
	{
		dir = UP;
		velX = 0;
	}
	else if (keyStates[SDL_SCANCODE_DOWN])
	{
		dir = DOWN;
		velX = 0;
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
			_shoot = true;
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

void Player::render()
{
	animation.renderFrame(position.x, position.y);
}

void Player::update(LevelEntities& entities)
{
	moveX();

	for (auto e = entities.enemies.begin(); e < entities.enemies.end(); ++e)
	{
		if (checkCollision(*e))
			handleCollisionX(*e);
	}

	int sz = entities.tileSize;
	int minX = position.x;
	int maxX = position.x + width;

	int minY = position.y;
	int maxY = position.y + height;

	//will throw std::out_of_range if player goes off screen!
	for (int x = minX/sz; x <= maxX/sz; ++x)
	{
		for(int y = minY/sz; y <= maxY/sz; ++y)
		{
			entities.tiles[y][x].changeImage(test);
			Tile& tile = entities.tiles[y][x];
			if(tile.tileType == 1 && checkCollision(tile))
			{
				handleCollisionX(tile);
			}
		}
	}

	moveY();

	for (auto e = entities.enemies.begin(); e < entities.enemies.end(); ++e)
	{
		if (checkCollision(*e))
			handleCollisionY(*e); //double
	}


	for (int x = position.x/sz; x <= (position.x+width)/sz; ++x)
	{
		for(int y = position.y/sz; y <= (position.y+height)/sz; ++y)
		{
			entities.tiles[y][x].changeImage(test);
			Tile& tile = entities.tiles[y][x];
			if(tile.tileType == 1 && checkCollision(tile))
			{
				handleCollisionY(tile);
			}
		}
	}


	if (_shoot)
		shoot(entities);

}

void Player::jump()
{
	if (!falling)
	{
		velY = JUMP_VELOCITY;
		falling = true;
	}
}

void Player::shoot(LevelEntities& entities)
{
	entities.playerProjectiles.push_front(PlayerProjectile(position, 30, &projectileAnimation, dir));
	_shoot = false;
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