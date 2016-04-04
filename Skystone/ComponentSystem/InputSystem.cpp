#include "InputSystem.h"

#include "Components/InputComponent.h"

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::handleInput(Scene& scene, SDL_Event& e)
{
	for (size_t i = 0; i < components_.size(); /*EMPTY*/)
	{
		auto& component = components_[i];
		if (component->owned())
		{
			component->handleInput(scene, e);
			++i;
		}
		else
		{
			ComponentSystem::vector_remove(components_, i);
		}
	}
}

void InputSystem::addComponent(std::shared_ptr<Component> component)
{
	components_.push_back(std::static_pointer_cast<InputComponent>(component));
}
