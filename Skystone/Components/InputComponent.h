#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "Component.h"
#include "SDL\SDL.h"

class InputComponent : public Component
{
public:
	InputComponent(GameObject& owner);
	virtual ~InputComponent();

	virtual void handleInput(SDL_Event& e) = 0;

	virtual Component::Type getType();
};

#endif //INPUT_COMPONENT_H