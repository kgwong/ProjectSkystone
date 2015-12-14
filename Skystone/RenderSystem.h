#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <memory>

class Level;
class GameWindow;
class RenderComponent;

class RenderSystem
{
public:
	static const int NUM_LAYERS = 10;

public:
	RenderSystem();
	~RenderSystem();

	void addComponent(std::shared_ptr<RenderComponent> component);
	void update(Level& level, GameWindow& window);

private:
	std::vector<std::vector<std::shared_ptr<RenderComponent>>> renderLayers_;
};

#endif //RENDER_SYSYEM_H
