#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

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

	template <typename T, typename... Args>
	std::shared_ptr<T> getNewRenderer(Args&& ...args);

	template <typename T>
	static void vector_remove(std::vector<T>& v, int index);

	template <typename T>
	static void vector_remove(T& container, typename T::iterator it);

public:
	RenderSystem renderSystem_;
};

template<typename T, typename ...Args>
std::shared_ptr<T> ComponentSystem::getNewRenderer(Args&& ...args)
{
	std::shared_ptr<T> renderer = std::make_shared<T>(args...);
	renderSystem_.addComponent(renderer);
	return renderer;
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