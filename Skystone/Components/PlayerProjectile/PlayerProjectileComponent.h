#ifndef PLAYER_PROJECTILE_COMPONENT_H
#define PLAYER_PROJECTILE_COMPONENT_H

#include "Components/UpdatingComponent.h"


class PlayerProjectileComponent : public UpdatingComponent
{
public:
	PlayerProjectileComponent(GameObject& owner);
	virtual ~PlayerProjectileComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);
};


#endif //PLAYER_PROJECTILE_COMPONENT_H
