#include "Level.h"

#include "Game/GameConstants.h"
#include "LevelLoader.h"
#include "LevelMap.h"
#include "LevelManager.h"

#include "Components/Render/ScrollingSpriteRenderer.h"

#include "Components/Physics/PhysicsComponent.h" //
#include "GameMath/CircleMath.h" //
#include "Components/Player/PlayerControlComponent.h"
#include "StickOnCollision.h"
#include "Application/Log.h"
#include "GameObject/Builders/GameObjectBuilder.h"

GameObjectBuilder Level::gameObjectBuilder_;

Level::Level(int levelID)
	: levelManager_(nullptr),
	background_(nullptr),
	levelID_(levelID)
{
}

Level::~Level()
{
}

GameObject* Level::getCameraFollowObject()
{
	return &gameObjects.getPlayer();
}

void Level::onEnter()
{
	gameObjects.getPlayer().registerComponents(componentSystem_);
	gameObjects.start();
}

void Level::onExit()
{
	/*if (playerHook)
	{
		this->gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(true);
		playerHook->kill();
		playerHook = nullptr;
	}*/
	
	//should be one game object not a vector.
	//ObjectVector& playerHook = gameObjects.get(GameObject::Type::PLAYER_HOOK);
	//for (auto& p : playerHook)
	//	p->disownComponents();
	//shared ptr.
	if (gameObjects.playerHook != nullptr)
	{
		gameObjects.playerHook->kill();
		gameObjects.playerHook = nullptr;
	}
	//raw pointer.
	//gameObjects.getHook().disownComponents();
	gameObjects.getPlayer().disownComponents();
	ObjectVector& playerProjectiles = gameObjects.get(GameObject::Type::PLAYER_PROJECTILE);
	for (auto& p : playerProjectiles)
		p->disownComponents();
	playerProjectiles.clear();
	componentSystem_.cleanup();
}

void Level::setLevelManager(LevelManager* levelManager)
{
	levelManager_ = levelManager;
}

LevelManager* Level::getLevelManager()
{
	return levelManager_;
}

//void Level::addPlayerHookAtLocation(Point position, int velocity, double degrees)
//{
//	std::cout << "Player refCount: " << playerHook.use_count() << std::endl;
//
//	if (playerHook == nullptr)
//	{
//		auto hookToFling = gameObjectBuilder_.buildPlayerHook(componentSystem_, "");
//		hookToFling->setPos(position);
//		playerHook = std::move(hookToFling);
//		auto physics = playerHook->getComponent<PhysicsComponent>();
//		physics->enableGravity(false);
//
//		//use float here
//		int newVelX = (int)(velocity * cos(toRadians(degrees)));
//		int newVelY = (int)(velocity * sin(toRadians(degrees)));
//		physics->setVelX(newVelX * 60.0f);
//		physics->setVelY(newVelY * 60.0f);
//		playerHook->startComponents(*this);
//	}
//	//if the hook is rendered on the map
//	if (playerHook != nullptr)
//	{
//		PlayerControlComponent * playerControls = gameObjects.getPlayer().getComponent<PlayerControlComponent>();
//		StickOnCollision * hookState = playerHook->getComponent<StickOnCollision>();
//		//if hook is attached to a tile and player pressed D to launch hook..
//		if (playerControls != nullptr && hookState != nullptr
//			&& hookState->isConnected == true
//			&& playerControls->HookKeyInput == GameInputs::getKeycode(LAUNCH_HOOK))
//		{
//			this->gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(true);
//			playerHook->kill();
//			playerHook = nullptr;
//		}
//	}
//}

void Level::update()
{
	updatePlayer();
	Scene::update();
}

void Level::updatePlayer()
{
	GameObject& player = gameObjects.getPlayer();
	oldPlayerBlock_ = Block::getBlock(player.getPos());
	oldPlayerPosInBlock_ = Point{ (int)player.getPosX() % Constants::BLOCK_WIDTH_IN_PIXELS,
		(int)player.getPosY() % Constants::BLOCK_HEIGHT_IN_PIXELS };

	if (!player.alive())
	{
		player.broadcastEvent(ComponentEvent(ComponentEvent::Type::onDeath, *this));
	}
}

int Level::getID()
{
	return levelID_;
}

void Level::setNextLevel(Direction dir)
{
	LevelMap* levelMap = levelManager_->getLevelMap();
	Block nextBlock = levelMap->getAdjBlock(oldPlayerBlock_ + levelMap->getBaseBlock(levelID_), dir);
	int nextLevelID = levelMap->getLevelID(nextBlock);

	Block nextBaseBlock = levelMap->getBaseBlock(nextLevelID);
	Block newRelativeBlock{ nextBlock.r - nextBaseBlock.r,
							nextBlock.c - nextBaseBlock.c };
	

	switch (dir)
	{
	case Direction::UP:
		oldPlayerPosInBlock_.y = Constants::BLOCK_HEIGHT_IN_PIXELS - 2 * Constants::TILE_SIZE;
		break;
	case Direction::DOWN:
		oldPlayerPosInBlock_.y = 2 * Constants::TILE_SIZE;
		break;
	case Direction::LEFT:
		oldPlayerPosInBlock_.x = Constants::BLOCK_WIDTH_IN_PIXELS - 2 * Constants::TILE_SIZE;
		break;
	case Direction::RIGHT:
		oldPlayerPosInBlock_.x = 2 * Constants::TILE_SIZE;
		break;
	}


	Point newPlayerPosition{ newRelativeBlock.c * Constants::BLOCK_WIDTH_IN_PIXELS + oldPlayerPosInBlock_.x,
								newRelativeBlock.r * Constants::BLOCK_HEIGHT_IN_PIXELS + oldPlayerPosInBlock_.y};

	levelManager_->setNextLevel(nextLevelID, newPlayerPosition);
}

int Level::getWidth()
{
	return gameObjects.getTiles().cols * Constants::TILE_SIZE;
}

int Level::getHeight()
{
	return gameObjects.getTiles().rows * Constants::TILE_SIZE;
}