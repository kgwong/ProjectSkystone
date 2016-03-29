#ifndef ENEMY_PROJECTILE_COMPONENT_H
#define ENEMY_PROJECTILE_COMPONENT_H

#include "Components/NonUpdatingComponent.h"


class EnemyProjectileComponent :
	public NonUpdatingComponent
{
public:
	EnemyProjectileComponent(GameObject& owner);
	virtual ~EnemyProjectileComponent();

	virtual void start(Scene& scene);
};

#endif //ENEMY_PROJECTILE_COMPONENT_H