#include "BurnTileComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Common/HealthComponent.h"
#include <iostream>
#include "Application/Log.h"
using namespace std;



BurnTileComponent::BurnTileComponent(GameObject & owner)
	: SpecialTileComponent(owner),
	damage_value_(DEFAULT_DAMAGE),
	delay_(DEFAULT_DELAY),
	slow_(DEFAULT_SLOW),
	time_(0)
{
}

BurnTileComponent::~BurnTileComponent()
{
}

void BurnTileComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	playerPhysics_ = scene.gameObjects.getPlayer().getComponent<PhysicsComponent>();
	health_ = scene.gameObjects.getPlayer().getComponent<HealthComponent>();
	damage_ = owner_.getComponent<DamageComponent>();

}

void BurnTileComponent::update(Scene& scene)
{
	if (playerPhysics_->isFalling()) //if you jumped off the tile, stop the slowing accel
	{
		playerPhysics_->setAccelX(0);
	}
}


void BurnTileComponent::handleEvent(const CollisionEvent & other)
{
	if (other.getOtherObject().getType() == GameObject::Type::PLAYER)
	{
		float currentSpeed = playerPhysics_->getVelX();
		int direction = 1;
		if (playerPhysics_->isMovingRight()) //determine which direction to slow you
		{
			direction = -1;
		}
		
		//slow/push them if they're moving and aren't being slowed already
		if (playerPhysics_->getVelX() != 0 && playerPhysics_->getAccelX() == 0)
		{

			playerPhysics_->setAccelX(slow_ * direction * 3600.0f);


			time_++;
		}
		//don't push them if they're just standing on it
		else
		{
			playerPhysics_->setAccelX(0);
		}
	}
	if (time_++ > delay_)
	{
		health_->takeDamage(damage_->getDamage());
		cout << "Took " << damage_->getDamage() << " damage!" << endl;
		cout << "Current hp: " << health_->getHealth() << endl;

		time_ = 0;

	}
}