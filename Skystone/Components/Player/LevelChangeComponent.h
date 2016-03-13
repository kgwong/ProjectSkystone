#ifndef LEVEL_CHANGE_COMPONENT_H
#define LEVEL_CHANGE_COMPONENT_H

#include "Components/UpdatingComponent.h"
#include "Components/Collider/ColliderComponent.h"

class LevelChangeComponent : public UpdatingComponent
{
public:
	LevelChangeComponent(GameObject& owner);
	virtual ~LevelChangeComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	ColliderComponent* collider_;
};

#endif //LEVEL_CHANGE_COMPONENT_H