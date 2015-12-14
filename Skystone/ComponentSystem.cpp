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
}

void ComponentSystem::render(Level& level, GameWindow& window)
{
	renderSystem_.update(level, window);
}