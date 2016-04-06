#ifndef BOSS_CLAW_PROJECTILE_BUILDER_H
#define BOSS_CLAW_PROJECTILE_BUILDER_H
#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class BossClawProjectileBuilder
{
public:
	BossClawProjectileBuilder();
	virtual ~BossClawProjectileBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name);
};

#endif //BOSS_CLAW_PROJECTILE_BUILDER_H