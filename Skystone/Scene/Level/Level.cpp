#include "Level.h"

#include "Game/GameConstants.h"
#include "LevelLoader.h"
#include "LevelMap.h"
#include "LevelManager.h"

#include "Application/Log.h"

#include "Components\Events\ComponentEvent.h"
#include "Components/Player/PlayerControlComponent.h"

Level::Level(int levelID)
	: levelManager_(nullptr),
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
	LOG("FLAPJACKS") << "enter level";
	LOG("FLAPJACKS") << gameObjects.getPlayer().getComponent<PlayerControlComponent>()->HookState().getState()->name();
	gameObjects.getPlayer().getComponent<PlayerControlComponent>()->HookState().resetState();
	LOG("FLAPJACKS") << gameObjects.getPlayer().getComponent<PlayerControlComponent>()->HookState().getState()->name();
}


void Level::onExit()
{
	LOG("FLAPJACKS") << "EXIT LEVEL";
	if (gameObjects.playerHook != nullptr)
	{
		gameObjects.playerHook->kill();
		gameObjects.playerHook = nullptr;
	}
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