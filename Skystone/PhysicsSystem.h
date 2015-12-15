#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <memory>
#include <vector>

class PhysicsComponent;
class Level;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void addComponent(std::shared_ptr<PhysicsComponent> component);
	void update(Level& level);

private:
	std::vector<std::shared_ptr<PhysicsComponent>> components_;
};

#endif //PHYSICS_SYSTEM_H