#include "GameObjectContainer.h"

#include "Components/Events/ComponentEvent.h"
#include "Application/Log.h"

// duct taping code together
#include "Components/Render/SpriteRenderer.h"
#include "Resources/Resources.h"

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
		newObject = builder_.buildEnemyProjectile(componentSystem_, name);
		objects_[GameObject::Type::ENEMY_PROJECTILE].push_back(newObject);
	}
	else if (type == "PlayerHook")
	{
		if (playerHook != nullptr)
		{
			playerHook->kill();
			playerHook = nullptr;
		}
		
		newObject = builder_.buildPlayerHook(componentSystem_, name);
		playerHook = newObject;
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
	//duct taping code together
	else if (type == "Background")
	{
		//newObject = std::make_shared<GameObject>();
		//newObject->setType(GameObject::Type::BACKGROUND);
		//objects_[GameObject::Type::BACKGROUND].push_back(newObject);
		//SpriteSheet* sprite = Resources::getSpriteSheet("Assets/GameOverScreen.png");
		//newObject->addComponent(componentSystem_.getNew<SpriteRenderer>(*newObject, sprite));
		newObject = builder_.buildBackground(componentSystem_, name);
		objects_[GameObject::Type::BACKGROUND].push_back(newObject);
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
	for (size_t i = 0; i < vector.size(); /*empty*/)
	{
		auto& obj = vector[i];
		if (!obj->alive())
		{
			obj->broadcastEvent(ComponentEvent(ComponentEvent::Type::onDeath, scene));
			ComponentSystem::vector_remove(vector, i);
		}
		else
		{
			++i;
		}
	}
}

GameObject& GameObjectContainer::getHook()
{
	return *hook_;
}
void GameObjectContainer::setHook(GameObject* hook)
{
	hook_ = hook;
}



