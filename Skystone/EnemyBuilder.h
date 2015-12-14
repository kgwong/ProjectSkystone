#ifndef ENEMY_BUILDER_H
#define ENEMY_BUILDER_H

#include <string>

class TextureLoader;
class Enemy;
class ComponentSystem;

class EnemyBuilder
{
public:
	EnemyBuilder(TextureLoader* textureLoader);
	virtual ~EnemyBuilder();

	Enemy& build(ComponentSystem& componentSystem, const std::string& enemyName, Enemy& enemyToBuild);
	
private:
	TextureLoader* textureLoader_;
};

#endif //ENEMY_BUILDER_H