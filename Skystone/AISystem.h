#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include <memory>
#include <vector>

class Level;
class AIComponent;

class AISystem
{
public:
	AISystem();
	~AISystem();

	void addComponent(std::shared_ptr<AIComponent> component);
	void update(Level& level);

private:
	std::vector<std::shared_ptr<AIComponent>> components_;
};

#endif //AI_SYSTEM_H