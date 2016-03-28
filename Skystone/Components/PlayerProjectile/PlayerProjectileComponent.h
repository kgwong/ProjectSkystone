#ifndef PLAYER_PROJECTILE_COMPONENT_H
#define PLAYER_PROJECTILE_COMPONENT_H

#include "Components/NonUpdatingComponent.h"


class PlayerProjectileComponent : public NonUpdatingComponent
{
public:
	PlayerProjectileComponent(GameObject& owner);
	virtual ~PlayerProjectileComponent();

	virtual void start(Scene& scene);
};


#endif //PLAYER_PROJECTILE_COMPONENT_H
