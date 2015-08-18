#include "Player.h"

#include "Level.h"
#include "PhysicsComponent.h"
#include "AnimationRenderer.h"

Player::Player(ResourceLocator* resourceLocator)
	: dir(Direction::RIGHT), 
	_animation(resourceLocator->getAnimation("Assets/Animations/playerAnimation.png")),
	_renderComponent(new AnimationRenderer(_animation)),
	_colliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight()),
	_shoot(false)
{
}

Player::~Player()
{
}

void Player::handleInput2()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	if(keyStates[SDL_SCANCODE_LEFT])
	{
		_physicsComponent.setVelX(-5);
		dir = Direction::LEFT;
	}
	else if(keyStates[SDL_SCANCODE_RIGHT])
	{
		_physicsComponent.setVelX(5);
		dir = Direction::RIGHT;
	}
	else if (keyStates[SDL_SCANCODE_UP])
	{
		dir = Direction::UP;
		_physicsComponent.setVelX(0);
	}
	else if (keyStates[SDL_SCANCODE_DOWN])
	{
		dir = Direction::DOWN;
		_physicsComponent.setVelX(0);
	}
	else
		_physicsComponent.setVelX(0);

}

void Player::handleInput(SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
		case SDLK_a:
			jump();
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
	_colliderComponent.update(*this);
	_physicsComponent.update(*this, level, &_colliderComponent);

	if (_shoot)
		shoot(level);

}

void Player::jump()
{
	if (!_physicsComponent.isFalling())
		_physicsComponent.setVelY(JUMP_VELOCITY);
}

void Player::shoot(Level& level)
{
	level.addPlayerProjectileAtLocation(position, 30, dir);
	_shoot = false;
}


Component* Player::getComponent(ComponentType type)
{
	if (type == ComponentType::COLLIDER)
		return &_colliderComponent;
	else 
		return nullptr;
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