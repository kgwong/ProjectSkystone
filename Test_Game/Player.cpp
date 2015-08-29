#include "Player.h"

#include "Level.h"
#include "PhysicsComponent.h"
#include "AnimationRenderer.h"

#include "TestPlayerStates.h"
#include "Log.h"

Player::Player(TextureLoader* textureLoader)
	: dir(Direction::RIGHT),
	_renderComponent(new AnimationRenderer(textureLoader->getTextureSheet("Assets/Animations/playerAnimation.png"))),
	_colliderComponent(new ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())),
	_healthComponent(new HealthComponent(100)),
	_physicsComponent(new PhysicsComponent()),
	_shoot(false), 
	currState_(&states::walkingState)
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
}

void Player::handleInput(SDL_Event &e)
{
	currState_->handleInput(*this, e);
}


void Player::update(Level& level)
{
	//LOG << "Current State: " << currState_->name();
	currState_->update(*this);
	_colliderComponent->update(*this);
	_physicsComponent->update(*this, level, _colliderComponent.get());


	if (_shoot)
		shoot(level);


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

void Player::render()
{
	_renderComponent->update(*this);
}

void Player::changeState(PlayerState* state)
{
	currState_ = state;
	currState_->onEnter(*this);
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