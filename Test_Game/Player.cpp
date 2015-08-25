#include "Player.h"

#include "Level.h"
#include "PhysicsComponent.h"
#include "AnimationRenderer.h"

Player::Player(TextureLoader* textureLoader)
	: dir(Direction::RIGHT),
	_renderComponent(new AnimationRenderer(textureLoader->getTextureSheet("Assets/Animations/playerAnimation.png"))),
	_colliderComponent(new ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())),
	_healthComponent(new HealthComponent(100)),
	_physicsComponent(new PhysicsComponent()),
	_shoot(false), 
	_flying(false)
{
	addComponent(_renderComponent.get());
	addComponent(_physicsComponent.get());
	addComponent(_healthComponent.get());
	addComponent(_colliderComponent.get());
}

Player::~Player()
{
}

void Player::handleInput2()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	_physicsComponent->setVelX(0);


	if (_flying)
	{
		if (keyStates[SDL_SCANCODE_LEFT])
		{
			_physicsComponent->setVelX(-5);
			dir = Direction::LEFT;
		}
		if (keyStates[SDL_SCANCODE_RIGHT])
		{
			_physicsComponent->setVelX(5);
			dir = Direction::RIGHT;
		}
		if (keyStates[SDL_SCANCODE_A])
		{
			_physicsComponent->setVelY(0);
		}
		else
			_flying = false;
		if (keyStates[SDL_SCANCODE_UP])
		{
			dir = Direction::UP;
			_physicsComponent->setVelY(-5);
		}

		if (keyStates[SDL_SCANCODE_DOWN])
		{
			dir = Direction::DOWN;
			_physicsComponent->setVelY(5);
		}


	}
	else
	{
		if (keyStates[SDL_SCANCODE_LEFT])
		{
			_physicsComponent->setVelX(-5);
			dir = Direction::LEFT;
		}
		if (keyStates[SDL_SCANCODE_RIGHT])
		{
			_physicsComponent->setVelX(5);
			dir = Direction::RIGHT;
		}
		if (keyStates[SDL_SCANCODE_UP])
		{
			dir = Direction::UP;
		}
		if (keyStates[SDL_SCANCODE_DOWN])
		{
			dir = Direction::DOWN;
		}
	}
}

void Player::handleInput(SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
		case SDLK_a:
			if (!_physicsComponent->isFalling())
				jump();
			else
				_flying = true;
			break;
		case SDLK_s:
			_shoot = true;
			break;
		default:
			break;
	}
}

void Player::render()
{
	_renderComponent->update(*this);
}

void Player::update(Level& level)
{
	_colliderComponent->update(*this);
	_physicsComponent->update(*this, level, _colliderComponent.get());

	if (_shoot)
		shoot(level);

	if (!_physicsComponent->isFalling())
		_flying = false; 

	/*
	if (_flying)
		std::cout << "Flying" << std::endl;
	else
		std::cout << "g" << std::endl;*/

	if (_colliderComponent->getLeft() < 0)
		level.setNextLevel(_oldBlock, _oldPosInBlock, Direction::LEFT );
	else if (_colliderComponent->getRight() > level.getLevelWidth())
		level.setNextLevel(_oldBlock, _oldPosInBlock, Direction::RIGHT);
	else if (_colliderComponent->getTop() < 0)
		level.setNextLevel(_oldBlock, _oldPosInBlock, Direction::UP);
	else if (_colliderComponent->getBottom() > level.getLevelHeight())
		level.setNextLevel(_oldBlock, _oldPosInBlock, Direction::DOWN);
	
	_oldBlock = Block::getBlock(getPos());
	_oldPosInBlock = Point{ getPosX() % Constants::BLOCK_WIDTH_IN_PIXELS,
							getPosY() % Constants::BLOCK_HEIGHT_IN_PIXELS };
}

void Player::jump()
{
	_physicsComponent->setVelY(JUMP_VELOCITY);
}

void Player::shoot(Level& level)
{
	level.addPlayerProjectileAtLocation(position, 30, dir);
	_shoot = false;
}

std::string Player::getName() const
{
	return "Player";
}

EntityType Player::getType() const
{
	return EntityType::PLAYER;
}

void Player::onCollision(CollisionInfo& collision)
{
	if (collision.other.getType() == EntityType::PICKUP)
	{
		std::cout << "thing acquired! yay!" << std::endl;
	}
}