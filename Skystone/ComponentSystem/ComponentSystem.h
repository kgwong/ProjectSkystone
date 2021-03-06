#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "RenderSystem.h"
#include "ComponentSubsystem.h"
#include "InputSystem.h"
#include "SDL\SDL.h"

class Scene;
class GameWindow;

class ComponentSystem
{
public:
	ComponentSystem();
	~ComponentSystem();

	void handleInput(Scene& scene, SDL_Event& e);
	void update(Scene& scene);
	void render(Scene& scene, GameWindow& window, float percBehind);

	void cleanup();

	void addComponent(std::shared_ptr<Component> component);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNew(Args&& ...args);

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

#endif //COMPONENT_SYSTEM_H