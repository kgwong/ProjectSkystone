#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <vector>
#include <memory>

#include <SDL\SDL.h>

class Component;
class InputComponent;

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void handleInput(SDL_Event& e);

	void addComponent(std::shared_ptr<Component> component);

private:
	std::vector<std::shared_ptr<InputComponent>> components_;
};

#endif //INPUT_SYSTEM_H