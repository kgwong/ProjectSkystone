#include "PhysicsSystem.h"

#include "PhysicsComponent.h"


PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::addComponent(std::shared_ptr<Component> component)
{
	components_.push_back(component);
}

void PhysicsSystem::update(Level& level)
{
	for (int i = 0; i < components_.size(); /*EMPTY*/)
	{
		auto& component = components_[i];
		if (component->owned())
		{
			component->update(level);
			++i;
		}
		else
		{
			ComponentSystem::vector_remove(components_, i);
		}
	}
}
