#ifndef GAME_OBJECT_CONTAINER_H
#define GAME_OBJECT_CONTAINER_H

#include <string>
#include <unordered_map>

#include "GameObject.h"
#include "Builders/GameObjectBuilder.h"
#include "ComponentSystem/ComponentSystem.h"
#include "TileArrangement.h"

typedef std::vector<std::shared_ptr<GameObject>> ObjectVector;
typedef std::unordered_map<GameObject::Type, ObjectVector> ObjectMap;

class GameObjectContainer
{
public:
	static GameObjectBuilder builder_;

public:	
	GameObjectContainer(Scene& scene, ComponentSystem& componentSystem);
	~GameObjectContainer();

	void start();
	void update();

	void buildTile(int tileType, GameObject& tileToBuild);
	std::shared_ptr<GameObject> add(const std::string& type, const std::string& name);
	std::shared_ptr<GameObject> add(const std::string& type, const std::string& name, const Point& startPos);

	GameObject& getPlayer();
	void setPlayer(GameObject* player);

	TileArrangement& getTiles();
	ObjectVector& get(GameObject::Type type);

	std::shared_ptr<GameObject> playerHook;

	//GameObject& getHook();
	//void setHook(GameObject* hook);

private:
	Scene& scene_;
	ComponentSystem& componentSystem_;

	GameObject* player_;
	TileArrangement tileArrangement_;
	ObjectMap objects_;

	GameObject* hook_;

public: //should be private
	void removeDeadObjects(ObjectVector& vector, Scene& scene);
};


#endif // GAME_OBJECT_CONTAINER_H

