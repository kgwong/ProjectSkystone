#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include <memory>
#include <vector>

class Level;
class Component;

class AISystem
{
public:
	AISystem();
	~AISystem();

	void addComponent(std::shared_ptr<Component> component);
	void update(Level& level);

private:
	std::vector<std::shared_ptr<Component>> components_;
};

#endif //AI_SYSTEM_H