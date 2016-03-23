#include "RenderSystem.h"

#include "Components/Render/RenderComponent.h"

RenderSystem::RenderSystem()
	:renderLayers_(10)
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::addComponent(std::shared_ptr<Component> component)
{
	//dynamic cast?
	auto c = std::static_pointer_cast<RenderComponent>(component);
	renderLayers_[c->getRenderLayer()].push_back(c);
}

void RenderSystem::update(Scene& scene)
{
	for (auto& layer : renderLayers_)
	{
		for (size_t i = 0; i < layer.size(); /*EMPTY*/)
		{
			auto& component = layer[i];
			if (component->owned())
			{
				component->update(scene);
				++i;
			}
			else
			{
				ComponentSystem::vector_remove(layer, i);
			}
		}
	}
}

void RenderSystem::update(Scene& scene, GameWindow& window, float percBehind)
{
	for (auto& layer : renderLayers_)
	{
		for (size_t i = 0; i < layer.size(); /*empty*/ )
		{
			auto& component = layer[i];
			if (component->owned())
			{
				component->render(window, percBehind);
				++i;
			}
			else
			{
				ComponentSystem::vector_remove(layer, i);
			}
		}
	}
}

void RenderSystem::cleanup()
{
	for (auto& layer : renderLayers_)
	{
		for (size_t i = 0; i < layer.size(); /*empty*/)
		{
			auto& component = layer[i];
			if (component->owned())
			{
				++i;
			}
			else
			{
				ComponentSystem::vector_remove(layer, i);
			}
		}
	}
}
