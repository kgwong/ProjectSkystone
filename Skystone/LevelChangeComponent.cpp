#include "LevelChangeComponent.h"



LevelChangeComponent::LevelChangeComponent()
	:collider_(nullptr)
{
}


LevelChangeComponent::~LevelChangeComponent()
{
}

void LevelChangeComponent::start(GameObject& owner, Level& level)
{
	collider_ = owner.getComponent<ColliderComponent>();
}

void LevelChangeComponent::update(GameObject& owner, Level& level)
{
	if (collider_->getLeft() < 0)
		level.setNextLevel(Direction::LEFT);
	else if (collider_->getRight() > level.getLevelWidth())
		level.setNextLevel(Direction::RIGHT);
	else if (collider_->getTop() < 0)
		level.setNextLevel(Direction::UP);
	else if (collider_->getBottom() > level.getLevelHeight())
		level.setNextLevel(Direction::DOWN);
}
