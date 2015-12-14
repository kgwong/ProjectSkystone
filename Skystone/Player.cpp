#include "Player.h"

#include "TestPlayerStates.h"
#include "Log.h"
#include "TextureLoader.h"

#include "Level.h"
#include "PhysicsComponent.h"
#include "AnimationRenderer.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "DamageComponent.h"
#include "LevelChangeComponent.h"

#include "GameOverException.h"

Player::Player(TextureLoader* textureLoader)
	: degrees_(0),
	_renderComponent(new AnimationRenderer(*this, textureLoader->getTextureSheet("Assets/betterPlayer.png"))),
	_colliderComponent(new ColliderComponent(0, 0, _renderComponent->getWidth(), _renderComponent->getHeight())),
	_healthComponent(new HealthComponent(100)),
	_physicsComponent(new PhysicsComponent()),
	levelChangeComponent_(new LevelChangeComponent()),
	shoot_(false), 
	currState_(&states::walkingState),
	aimState_(AimState::RIGHT)
{
	addComponent(_renderComponent);
	addComponent(_physicsComponent);
	addComponent(_healthComponent);
	addComponent(_colliderComponent);
	addComponent(levelChangeComponent_);
}

Player::~Player()
{
}

void Player::handleInput2()
{

}

void Player::handleInput(SDL_Event &e)
{
	currState_->handleInput(*this, e);
	if (e.key.keysym.sym == controlMap[ATTACK])
		shoot_ = true;

	if (aimState_ == AimState::UP)
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
		{
			aimState_ = AimState::UP_LEFT;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
		{
			aimState_ = AimState::UP_RIGHT;
		}
		if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[UP])
		{
			aimState_ = prevAimState_;
		}
	}
	else
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
		{
			aimState_ = AimState::LEFT;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
		{
			aimState_ = AimState::RIGHT;
		}
		if (e.key.keysym.sym == controlMap[UP])
		{
			if (aimState_ == AimState::LEFT || aimState_ == AimState::RIGHT)
			{
				prevAimState_ = aimState_;
			}
			aimState_ = AimState::UP;
		}
	}
}

void Player::aim()
{
	switch (aimState_)
	{
	case AimState::UP:
		degrees_ = 270;
		break;
	case AimState::UP_LEFT:
		_physicsComponent->setVelX(0);
		degrees_ = 225;
		break;
	case AimState::UP_RIGHT:
		_physicsComponent->setVelX(0);
		degrees_ = 315;
		break;
	case AimState::LEFT:
		degrees_ = 180;
		break;
	case AimState::RIGHT:
		degrees_ = 0;
		break;
	}
}

void Player::update(Level& level)
{
	currState_->update(*this);

	aim();

	//_colliderComponent->update(*this, level);
	_physicsComponent->update(*this, level);

	if (shoot_)
		shoot(level);

	levelChangeComponent_->update(*this, level);
	_healthComponent->update(*this, level);
}

void Player::render(Level& level)
{
	_renderComponent->update(*this, level);
}

void Player::changeState(PlayerState* state)
{
	currState_->onExit(*this);
	currState_ = state;
	currState_->onEnter(*this);
	//LOG << "Current State: " << currState_->name(); 
}

void Player::jump()
{
	_physicsComponent->setVelY(JUMP_VELOCITY);
}

void Player::shoot(Level& level)
{
	level.addPlayerProjectileAtLocation(position_, Player::PROJECTILE_VELOCITY, degrees_);
	shoot_ = false;
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
	switch (collision.other.getType())
	{
	case EntityType::PICKUP:
		_healthComponent->heal(10);
		std::cout << "Picked up a thing to heal 10hp!" << std::endl;
		break;
	case EntityType::ENEMY:
		DamageComponent* damage = collision.other.getComponent<DamageComponent>();
		if (_healthComponent->takeDamage(damage->getDamage()))
		{
			onDamageTaken(collision.level);
		}
		break;
	}

}

void Player::onDeath(Level& level)
{
	throw GameOverException();
}

void Player::onDamageTaken(Level& level)
{
	std::cout << "Hit by enemy! " << _healthComponent->getHealth() << "hp left" << std::endl;
	_healthComponent->setInvincible(true);
	changeState(&states::stunState);
	if (_physicsComponent->isMovingLeft())
	{
		_physicsComponent->setVelX(10);
	}
	else
	{
		_physicsComponent->setVelX(-10);
	}
	_physicsComponent->setVelY(-10);
}
