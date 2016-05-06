#include "GameObjectContainer.h"

#include "ComponentEvents/ComponentEvent.h"
#include "ComponentEvents/OnDeathEvent.h"
#include "Application/Log.h"
#include "Util/vector_util.h"

GameObjectBuilder GameObjectContainer::builder_;

GameObjectContainer::GameObjectContainer(Scene& scene, ComponentSystem& componentSystem) : scene_(scene),
	componentSystem_(componentSystem),
	player_(nullptr)
{
}


GameObjectContainer::~GameObjectContainer()
{
}
	
void GameObjectContainer::start()
{
	for (int r = 0; r < tileArrangement_.rows; ++r)
	{
		for (int c = 0; c < tileArrangement_.cols; ++c)
		{
			tileArrangement_.tiles[r][c].startComponents(scene_);
		}
	}
	player_->startComponents(scene_);
}

void GameObjectContainer::update()
{
	for (auto& objVector : objects_)
	{
		removeDeadObjects(objVector.second, scene_);
	}
}

void GameObjectContainer::buildTile(int tileType, GameObject& tileToBuild)
{
	builder_.buildTile(componentSystem_, tileType, tileToBuild);
}

std::shared_ptr<GameObject> GameObjectContainer::add(const std::string& type, const std::string& name)
{
	return add(type, name, Point());
}

std::shared_ptr<GameObject> GameObjectContainer::add(const std::string& type, const std::string& name, const Point& startPos)
{
	std::shared_ptr<GameObject> newObject;
	if (type == "Player")
	{

	}
	else if (type == "PlayerProjectile")
	{
		newObject = builder_.buildPlayerProjectile(componentSystem_, name);
		objects_[GameObject::Type::PLAYER_PROJECTILE].push_back(newObject);
	}
	else if (type == "EnemyProjectile")
	{
		if (name == "AcidProjectile")
		{
			newObject = builder_.buildEnemyProjectile(componentSystem_, name);
			objects_[GameObject::Type::ENEMY_PROJECTILE].push_back(newObject);
		}
		else if (name == "ClawProjectile")
		{
			newObject = builder_.buildEnemyProjectile(componentSystem_, name);
			objects_[GameObject::Type::ENEMY_PROJECTILE].push_back(newObject);
		}
	}
	else if (type == "PlayerHook")
	{
		if (playerHook != nullptr)
		{
			playerHook->kill();
			playerHook = nullptr;
		}

		newObject = builder_.buildPlayerHook(componentSystem_, name);
	}
	else if (type == "Drop")
	{
		newObject = builder_.buildItemDrop(componentSystem_, name);
		objects_[GameObject::Type::DROP].push_back(newObject);
	}
	else if (type == "Enemy")
	{
		newObject = builder_.buildEnemy(componentSystem_, name);
		objects_[GameObject::Type::ENEMY].push_back(newObject);
	}
	else if (type == "Background")
	{
		newObject = builder_.buildBackground(componentSystem_, name);
		objects_[GameObject::Type::BACKGROUND].push_back(newObject);
	}
	else if (type == "ScrollingBackground")
	{
		newObject = builder_.buildScrollingBackground(componentSystem_, name);
		objects_[GameObject::Type::BACKGROUND].push_back(newObject);
	}
	else if (type == "GUI")
	{
		if (objects_[GameObject::Type::GUI].size() == 0)
		{
			// buttons go on the most recently constructed TextSelector
			// first GUI should be the TextSelector
			auto textSelector = builder_.buildGUI(componentSystem_, "TextSelector", player_);
			objects_[GameObject::Type::GUI].push_back(textSelector);
		}
		newObject = builder_.buildGUI(componentSystem_, name, player_);
		objects_[GameObject::Type::GUI].push_back(newObject);
	}
	else
	{
		LOG("Warning") << "Invalid game object type. No object created";
		return nullptr;
	}
	newObject->setPos(startPos);
	newObject->startComponents(scene_);
	return newObject;
}

GameObject& GameObjectContainer::getPlayer()
{
	return *player_;
}

void GameObjectContainer::setPlayer(GameObject* player)
{
	player_ = player;
}

TileArrangement& GameObjectContainer::getTiles() 
{
	return tileArrangement_;
}

ObjectVector& GameObjectContainer::get(GameObject::Type type)
{
	return objects_[type];
}

void GameObjectContainer::removeDeadObjects(ObjectVector& vector, Scene& scene)
{

	typedef std::shared_ptr<GameObject> obj;
	util::vector::remove(vector,
		[](obj& o) { return !o->alive(); },
		[&scene](obj& o) { o->broadcastEvent(OnDeathEvent(scene)); }
	);
}




