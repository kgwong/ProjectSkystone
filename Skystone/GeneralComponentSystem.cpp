#include "GeneralComponentSystem.h"

#include "Component.h"

GeneralComponentSystem::GeneralComponentSystem()
{
}


GeneralComponentSystem::~GeneralComponentSystem()
{
}

void GeneralComponentSystem::addComponent(std::shared_ptr<Component> component)
{
	components_.push_back(component);
}

void GeneralComponentSystem::update(Level& level)
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
