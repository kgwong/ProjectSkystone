#include "ComponentSystem.h"

#include "Level.h"

#include "RenderComponent.h"

ComponentSystem::ComponentSystem()
{
}


ComponentSystem::~ComponentSystem()
{
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