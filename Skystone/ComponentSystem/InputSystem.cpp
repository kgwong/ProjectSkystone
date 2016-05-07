#include "InputSystem.h"

#include "Components/InputComponent.h"
#include "Util/vector_util.h"

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::handleInput(Scene& scene, SDL_Event& e)
{
	typedef std::shared_ptr<InputComponent> comp;
	util::vector::update_or_remove(components_,
		[](comp& c) { return !c->owned(); },
		[&scene, &e](comp& c) { return c->handleInput(scene, e); }
	);
}

void InputSystem::addComponent(std::shared_ptr<Component> component)
{
	components_.push_back(std::static_pointer_cast<InputComponent>(component));
}
