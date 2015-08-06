#ifndef ENEMY_BUILDER_H
#define ENEMY_BUILDER_H

#include <string>

#include "ResourceLocator.h"

class Enemy;

class EnemyBuilder
{
public:
	EnemyBuilder(ResourceLocator* resourceLocator);
	virtual ~EnemyBuilder();

	Enemy* create(const std::string& enemyName);
	

private:
	ResourceLocator* _resourceLocator;
};

#endif //ENEMY_BUILDER_H