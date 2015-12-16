#ifndef COMPONENT_SUBSYSTEM_H
#define COMPONENT_SUBSYSTEM_H

#include <memory>
#include <vector>

class Level;
class Component;

class ComponentSubsystem
{
public:
	ComponentSubsystem();
	~ComponentSubsystem();

	void addComponent(std::shared_ptr<Component> component);
	void update(Level& level);

private:
	std::vector<std::shared_ptr<Component>> components_;
};

#endif //COMPONENT_SYSTEM_H