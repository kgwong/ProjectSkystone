#ifndef PLAYER_PROJECTILE_BUILDER_H
#define PLAYER_PROJECTILE_BUILDER_H

#include <string>

class PlayerProjectile;
class TextureLoader;
class ComponentSystem;

class PlayerProjectileBuilder
{
public:
	PlayerProjectileBuilder(TextureLoader* textureLoader);
	~PlayerProjectileBuilder();

	PlayerProjectile& build(ComponentSystem& componentSystem, const std::string& name, PlayerProjectile& projectileToBuild);

private:
	TextureLoader* textureLoader_;
};

#endif PLAYER_PROJECTILE_BUILDER_H