#include "PhysicsSystem.h"

#include "PhysicsComponent.h"


#include <iostream> //
PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::addComponent(std::shared_ptr<PhysicsComponent> component)
{
	components_.push_back(component);
	std::cout << "test" << std::endl;
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
