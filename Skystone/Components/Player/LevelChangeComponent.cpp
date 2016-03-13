#include "LevelChangeComponent.h"

#include "GameTypes/Direction.h"
#include "Scene/Level/Level.h"

LevelChangeComponent::LevelChangeComponent(GameObject& owner)
	: UpdatingComponent(owner),
	collider_(nullptr)
{
}


LevelChangeComponent::~LevelChangeComponent()
{
}

void LevelChangeComponent::start(Scene& scene)
{
	collider_ = owner_.getComponent<ColliderComponent>();
}

void LevelChangeComponent::update(Scene& scene)
{
	//
	Level& level = static_cast<Level&>(scene);
	if (collider_->getLeft() < 0)
		level.setNextLevel(Direction::LEFT);
	else if (collider_->getRight() > level.getWidth())
		level.setNextLevel(Direction::RIGHT);
	else if (collider_->getTop() < 0)
		level.setNextLevel(Direction::UP);
	else if (collider_->getBottom() > level.getHeight())
		level.setNextLevel(Direction::DOWN);
}
