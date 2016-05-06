#include "RenderSystem.h"

#include "Components/Render/RenderComponent.h"
#include "Util/vector_util.h"

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
		typedef std::shared_ptr<RenderComponent> comp;
		util::vector::update_or_remove(layer,
			[](comp& c) { return !c->owned(); },
			[&scene](comp& c) { return c->update(scene); }
		);
	}
}

void RenderSystem::update(Scene& scene, GameWindow& window, float percBehind)
{
	for (auto& layer : renderLayers_)
	{
		typedef std::shared_ptr<RenderComponent> comp;
		util::vector::update_or_remove(layer,
			[](comp& c) { return !c->owned(); },
			[&window, percBehind](comp& c) { return c->render(window, percBehind); }
		);
	}
}

void RenderSystem::cleanup()
{
	for (auto& layer : renderLayers_)
	{
		typedef std::shared_ptr<RenderComponent> comp;
		util::vector::remove(layer,
			[](comp& c) { return !c->owned(); }
		);
	}
}
