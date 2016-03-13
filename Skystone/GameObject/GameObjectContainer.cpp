#include "GameObjectContainer.h"

#include "Components/Events/ComponentEvent.h"
#include "Application/Log.h"

GameObjectBuilder GameObjectContainer::builder_;

GameObjectContainer::GameObjectContainer(Level& level, ComponentSystem& componentSystem)
	: level_(level),
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
			tileArrangement_.tiles[r][c].startComponents(level_);
		}
	}
	player_->startComponents(level_);
}

void GameObjectContainer::update()
{
	for (auto& objVector : objects_)
	{
		removeDeadObjects(objVector.second, level_);
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
	else if (type == "PlayerHook")
	{

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
	else
	{
		LOG("Warning") << "Invalid game object type. No object created";
		return nullptr;
	}
	newObject->setPos(startPos);
	newObject->startComponents(level_);
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

void GameObjectContainer::removeDeadObjects(ObjectVector& vector, Level& level)
{
	for (size_t i = 0; i < vector.size(); /*empty*/)
	{
		auto& obj = vector[i];
		if (!obj->alive())
		{
			obj->broadcastEvent(ComponentEvent(ComponentEvent::Type::onDeath, level));
			ComponentSystem::vector_remove(vector, i);
		}
		else
		{
			++i;
		}
	}
}
