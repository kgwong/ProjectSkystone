#ifndef ENEMY_BUILDER_H
#define ENEMY_BUILDER_H

#include <string>

#include "TextureLoader.h"

class Enemy;

class EnemyBuilder
{
public:
	EnemyBuilder(TextureLoader* textureLoader);
	virtual ~EnemyBuilder();

	Enemy* build(const std::string& enemyName, Enemy& enemyToBuild);
	

private:
	TextureLoader* textureLoader_;
};

#endif //ENEMY_BUILDER_H