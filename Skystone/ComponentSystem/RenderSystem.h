#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <memory>

class Level;
class GameWindow;
class Component;
class RenderComponent;

class RenderSystem
{
public:
	static const int NUM_LAYERS = 10;

public:
	RenderSystem();
	~RenderSystem();

	void addComponent(std::shared_ptr<Component> component);
	void update(Level& level);
	void update(Level& level, GameWindow& window, float percBehind);

	void cleanup();

private:
	std::vector<std::vector<std::shared_ptr<RenderComponent>>> renderLayers_;
};

#endif //RENDER_SYSYEM_H
