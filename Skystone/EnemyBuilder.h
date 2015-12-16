#ifndef ENEMY_BUILDER_H
#define ENEMY_BUILDER_H

#include <string>
#include <memory> 

class TextureLoader;
class GameObject;
class ComponentSystem;

class EnemyBuilder
{
public:
	EnemyBuilder(TextureLoader* textureLoader);
	virtual ~EnemyBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& enemyName);
	
private:
	TextureLoader* textureLoader_;
};

#endif //ENEMY_BUILDER_H