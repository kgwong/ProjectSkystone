#include "ComponentSystem.h"

#include "Level.h"

#include "RenderComponent.h"

#include "Log.h"
#include <memory>

ComponentSystem::ComponentSystem()
{
}


ComponentSystem::~ComponentSystem()
{
}

void ComponentSystem::handleInput(SDL_Event& e)
{
	inputSystem_.handleInput(e);
}

void ComponentSystem::update(Level& level)
{
	generalComponentSystem_.update(level);
	aiSystem_.update(level);
	physicsSystem_.update(level);
}

void ComponentSystem::render(Level& level, GameWindow& window)
{
	renderSystem_.update(level, window);
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
		LOG_COUT << "Warning: unknown component!";
		break;
	}
}
