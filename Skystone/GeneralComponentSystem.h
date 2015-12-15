#ifndef GENERAL_COMPONENT_SYSTEM_H
#define GENERAL_COMPONENT_SYSTEM_H

#include <memory>
#include <vector>

class Component;
class Level;

class GeneralComponentSystem
{
public:
	GeneralComponentSystem();
	~GeneralComponentSystem();


	void addComponent(std::shared_ptr<Component> component);
	void update(Level& level);

private:
	std::vector<std::shared_ptr<Component>> components_;
};

#endif //GENERAL_COMPONENT_SYSTEM_H