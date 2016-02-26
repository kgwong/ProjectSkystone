#include "LiftTileComponent.h"
#include "Components/Physics/PhysicsComponent.h"


LiftTileComponent::LiftTileComponent(GameObject & owner)
	: SpecialTileComponent(owner),
	xRadius_(DEFAULT_X_RADIUS),
	time_(0),
	delay_(DEFAULT_DELAY),
	lift_(DEFAULT_LIFT)
{
}


LiftTileComponent::~LiftTileComponent()
{
}

void LiftTileComponent::start(Level & level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	playerPhysics_ = level.player->getComponent<PhysicsComponent>();

}

void LiftTileComponent::update(Level & level)
{

	if (!playerPhysics_->gravityEnabled() && time_ >= delay_)
	{
		playerPhysics_->setAccelY(0);
		playerPhysics_->enableGravity(true);
		time_ = 0;

	}
	else
		time_++;
}

void LiftTileComponent::handleEvent(const CollisionEvent & other)
{

	if (other.getOtherObject().getType() == GameObject::Type::PLAYER)
	{
		playerPhysics_->enableGravity(false);
		playerPhysics_->setVelY(-DEFAULT_LIFT * 360);
	}
}

