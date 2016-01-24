#ifndef PLAYER_PROJECTILE_BUILDER_H
#define PLAYER_PROJECTILE_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class PlayerProjectileBuilder
{
public:
	PlayerProjectileBuilder();
	~PlayerProjectileBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name);
};

#endif //PLAYER_PROJECTILE_BUILDER_H