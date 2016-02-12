#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "RenderSystem.h"
#include "ComponentSubsystem.h"
#include "InputSystem.h"
#include "SDL\SDL.h"

class Level;
class GameWindow;

class ComponentSystem
{
public:
	ComponentSystem();
	~ComponentSystem();

	void handleInput(SDL_Event& e);
	void update(Level& level);
	void render(Level& level, GameWindow& window, float percBehind);

	void cleanup();

	void addComponent(std::shared_ptr<Component> component);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNew(Args&& ...args);

	template <typename T>
	static void vector_remove(std::vector<T>& v, int index);

public:
	InputSystem inputSystem_;
	ComponentSubsystem generalComponentSystem_;
	ComponentSubsystem aiSystem_;
	ComponentSubsystem physicsSystem_;
	RenderSystem renderSystem_;
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> ComponentSystem::getNew(Args && ...args)
{
	auto& newComponent = std::make_shared<T>(args...);
	addComponent(newComponent);
	return newComponent;
}

template <typename T>
void ComponentSystem::vector_remove(std::vector<T>& v, int index)
{
	v[index] = v.back();
	v.pop_back();
}

#endif //COMPONENT_SYSTEM_H