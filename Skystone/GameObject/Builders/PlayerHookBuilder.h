//adding my own builder for player hooks
//based on kevin's player projectile builder

#ifndef PLAYER_HOOK_BUILDER_H
#define PLAYER_HOOK_BUILDER_H

#include <string>
#include <memory>

//forward declarations ar fum.
class GameObject;
class ComponentSystem;

class PlayerHookBuilder
{
public:
	PlayerHookBuilder();
	~PlayerHookBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name);

};

#endif

