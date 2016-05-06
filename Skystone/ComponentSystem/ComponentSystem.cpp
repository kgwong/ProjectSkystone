#include "ComponentSystem.h"

#include "Scene/Scene.h"

#include "Components/Render/RenderComponent.h"

#include "Application/Log.h"
#include <memory>

ComponentSystem::ComponentSystem()
{
}


ComponentSystem::~ComponentSystem()
{
}

void ComponentSystem::handleInput(Scene& scene, SDL_Event& e)
{
	inputSystem_.handleInput(scene, e);
}

void ComponentSystem::update(Scene& scene)
{
	renderSystem_.update(scene);
	generalComponentSystem_.update(scene);
	aiSystem_.update(scene);
	physicsSystem_.update(scene);
}

void ComponentSystem::render(Scene& scene, GameWindow& window, float percBehind)
{
	renderSystem_.update(scene, window, percBehind);
}

void ComponentSystem::cleanup()
{
	generalComponentSystem_.cleanup();
	aiSystem_.cleanup();
	physicsSystem_.cleanup();
	renderSystem_.cleanup();
}

void ComponentSystem::addComponent(std::shared_ptr<Component> component)
{
	switch (component->getType())
	{
	case Component::Type::INPUT:
		//
		inputSystem_.addComponent(component);
		generalComponentSystem_.addComponent(component);
		break;
	case Component::Type::AI:
		aiSystem_.addComponent(component);
		break;
	case Component::Type::PHYSICS:
		physicsSystem_.addComponent(component);
		break;
	case Component::Type::RENDER:
		renderSystem_.addComponent(component);
		break;
	case Component::Type::NON_UPDATING:
		break;
	case Component::Type::UPDATING:
		generalComponentSystem_.addComponent(component);
		break;
	default:
		LOG("WARNING") << "Warning: unknown component!";
		break;
	}
}
