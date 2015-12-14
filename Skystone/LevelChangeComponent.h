#ifndef LEVEL_CHANGE_COMPONENT_H
#define LEVEL_CHANGE_COMPONENT_H

#include "Component.h"
#include "ColliderComponent.h"

class LevelChangeComponent : public Component
{
public:
	LevelChangeComponent(GameObject& owner);
	virtual ~LevelChangeComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	ColliderComponent* collider_;
};

#endif //LEVEL_CHANGE_COMPONENT_H