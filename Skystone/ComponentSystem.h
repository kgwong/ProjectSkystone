#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "GeneralComponentSystem.h"
#include "AISystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

class Level;
class GameWindow;

class ComponentSystem
{
public:
	ComponentSystem();
	~ComponentSystem();

	void update(Level& level);
	void render(Level& level, GameWindow& window);

	void addComponent(std::shared_ptr<Component> component);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNewRenderer(Args&& ...args);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNewAI(Args&& ...args);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNewPhysics(Args&& ...args);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNewNonUpdating(Args&& ...args);

	template <typename T, typename... Args>
	std::shared_ptr<T> getNewUpdating(Args&& ...args);

	template <typename T>
	static void vector_remove(std::vector<T>& v, int index);

	template <typename T>
	static void vector_remove(T& container, typename T::iterator it);

public:
	GeneralComponentSystem generalComponentSystem_;
	AISystem aiSystem_;
	PhysicsSystem physicsSystem_;
	RenderSystem renderSystem_;
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> ComponentSystem::getNewRenderer(Args&& ...args)
{
	std::shared_ptr<T> renderer = std::make_shared<T>(args...);
	renderSystem_.addComponent(renderer);
	return renderer;
}

template<typename T, typename ...Args>
inline std::shared_ptr<T> ComponentSystem::getNewAI(Args&& ...args)
{
	std::shared_ptr<T> ai = std::make_shared<T>(args...);
	aiSystem_.addComponent(ai);
	return ai;
}

template<typename T, typename ...Args>
inline std::shared_ptr<T> ComponentSystem::getNewPhysics(Args&& ...args)
{
	std::shared_ptr<T> physics = std::make_shared<T>(args...);
	physicsSystem_.addComponent(physics);
	return physics;
}

template<typename T, typename ...Args>
inline std::shared_ptr<T> ComponentSystem::getNewNonUpdating(Args&& ...args)
{
	return std::make_shared<T>(args...);
}

template<typename T, typename ...Args>
inline std::shared_ptr<T> ComponentSystem::getNewUpdating(Args && ...args)
{
	std::shared_ptr<T> physics = std::make_shared<T>(args...);
	generalComponentSystem_.addComponent(physics);
	return physics;
}

template <typename T>
void ComponentSystem::vector_remove(std::vector<T>& v, int index)
{
	v[index] = v.back();
	v.pop_back();
}

template <typename T>
void ComponentSystem::vector_remove(T& container, typename T::iterator it)
{
	*it = container.back();
	container.pop_back();
}

#endif //COMPONENT_SYSTEM_H