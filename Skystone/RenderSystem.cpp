#include "RenderSystem.h"

#include "RenderComponent.h"

RenderSystem::RenderSystem()
	:renderLayers_(10)
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::addComponent(std::shared_ptr<RenderComponent> component)
{
	renderLayers_[component->getRenderLayer()].push_back(component);
}

void RenderSystem::update(Level& level, GameWindow& window)
{
	for (auto& layer : renderLayers_)
	{
		for (int i = 0; i < layer.size(); /*empty*/ )
		{
			auto& component = layer[i];
			if (component->owned())
			{
				component->update(level);
				++i;
			}
			else
			{
				ComponentSystem::vector_remove(layer, i);
			}
		}
	}
}
