#include "Player.h"

#include "Level.h"

Player::Player(GameWindow* window, ResourceLocator* resourceLocator)
	:_window(window), dir(RIGHT), _animation(resourceLocator->getAnimation("Assets/Animations/playerAnimation.png")),
	 _renderComponent(_animation),
	 _shoot(false)
{
	width = _animation->getWidth();
	height = _animation->getHeight();
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
		dir = LEFT;
	}
	else if(keyStates[SDL_SCANCODE_RIGHT])
	{
		_physicsComponent.setVelX(5);
		dir = RIGHT;
	}
	else if (keyStates[SDL_SCANCODE_UP])
	{
		dir = UP;
		_physicsComponent.setVelX(0);
	}
	else if (keyStates[SDL_SCANCODE_DOWN])
	{
		dir = DOWN;
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
	_renderComponent.update(*this);
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


Component* Player::getComponent(const std::string& componentName)
{
	if (componentName == "Collider")
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
	return PLAYER;
}

void Player::onCollision(GameObject& other)
{
	if (other.getType() == PICKUP)
	{
		std::cout << "thing acquired! yay!" << std::endl;
	}
}