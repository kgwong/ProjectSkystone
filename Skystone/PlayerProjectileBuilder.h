#ifndef PLAYER_PROJECTILE_BUILDER_H
#define PLAYER_PROJECTILE_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class TextureLoader;
class ComponentSystem;

class PlayerProjectileBuilder
{
public:
	PlayerProjectileBuilder(TextureLoader* textureLoader);
	~PlayerProjectileBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name);

private:
	TextureLoader* textureLoader_;
};

#endif //PLAYER_PROJECTILE_BUILDER_H