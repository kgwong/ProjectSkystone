#ifndef ENEMY_PROJECTILE_BUILDER_H
#define ENEMY_PROJECTILE_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class EnemyProjectileBuilder
{
public:
	EnemyProjectileBuilder();
	 ~EnemyProjectileBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name);

};

#endif //ENEMY_PROJECTILE_BUILDER_H