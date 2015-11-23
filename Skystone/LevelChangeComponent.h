#ifndef LEVEL_CHANGE_COMPONENT_H
#define LEVEL_CHANGE_COMPONENT_H

#include "Component.h"
#include "ColliderComponent.h"

class LevelChangeComponent : public Component
{
public:
	LevelChangeComponent();
	virtual ~LevelChangeComponent();

	virtual void start(GameObject& owner, Level& level);
	virtual void update(GameObject& owner, Level& level);

private:
	ColliderComponent* collider_;
};

#endif //LEVEL_CHANGE_COMPONENT_H