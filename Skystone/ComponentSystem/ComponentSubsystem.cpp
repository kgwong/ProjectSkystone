#include "ComponentSubsystem.h"

#include "Components/Component.h"

ComponentSubsystem::ComponentSubsystem()
{
}


ComponentSubsystem::~ComponentSubsystem()
{
}

void ComponentSubsystem::addComponent(std::shared_ptr<Component> component)
{
	components_.push_back(component);
}

void ComponentSubsystem::update(Scene& scene)
{
	for (size_t i = 0; i < components_.size(); /*EMPTY*/)
	{
		auto& component = components_[i];
		if (component->owned())
		{
			component->update(scene);
			++i;
		}
		else
		{
			ComponentSystem::vector_remove(components_, i);
		}
	}
}

void ComponentSubsystem::cleanup()
{
	for (size_t i = 0; i < components_.size(); /*EMPTY*/)
	{
		auto& component = components_[i];
		if (component->owned())
		{
			++i;
		}
		else
		{
			ComponentSystem::vector_remove(components_, i);
		}
	}
}
