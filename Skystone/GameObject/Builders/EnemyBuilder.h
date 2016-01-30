#ifndef ENEMY_BUILDER_H
#define ENEMY_BUILDER_H

#include <string>
#include <memory> 

class GameObject;
class ComponentSystem;

class EnemyBuilder
{
public:
	EnemyBuilder();
	virtual ~EnemyBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& enemyName);
};

#endif //ENEMY_BUILDER_H