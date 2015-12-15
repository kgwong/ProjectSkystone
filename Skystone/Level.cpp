#include "Level.h"

#include "GameConstants.h"
#include "LevelLoader.h"
#include "LevelMap.h"
#include "LevelManager.h"
#include "TextureLoader.h"
#include "EnemyBuilder.h"
#include "TileBuilder.h"
#include "Background.h"

#include "PhysicsComponent.h" //
#include "CircleMath.h" //

Level::Level(int levelID)
	:levelManager_(nullptr),
	gameObjectBuilder_(nullptr),
	background_(nullptr),
	levelID_(levelID)
{
}

Level::~Level()
{
}

void Level::onEnter()
{
	startEntityComponents();
}

void Level::onExit()
{
	for (auto& p : playerProjectiles)
		p->clearComponents();
	playerProjectiles.clear();
}

void Level::setLevelManager(LevelManager* levelManager)
{
	levelManager_ = levelManager;
}

void Level::setGameObjectBuilder(GameObjectBuilder* gameObjectBuilder)
{
	gameObjectBuilder_ = gameObjectBuilder;
}

void Level::setBackgroundFromSprite(std::shared_ptr<SpriteRenderer> spriteRenderer)
{
	background_ = std::make_shared<Background>();
	background_->setType(ObjectType::BACKGROUND);
	background_->addComponent(componentSystem_.getNewRenderer<SpriteRenderer>(*background_, gameObjectBuilder_->getTexture("Assets/backgroundTest.png")));
}

void Level::setPlayer(Player* p, Point startPosition)
{
	player = p;
	player->setPos(startPosition);
}

Point Level::getPlayerPos()
{
	return player->getPos();
}

LevelManager * Level::getLevelManager()
{
	return levelManager_;
}

void Level::startEntityComponents()
{
	for (int r = 0; r < tileArrangement.rows; ++r)
		for (int c = 0; c < tileArrangement.cols; ++c)
			tileArrangement.tiles[r][c].startComponents(*this);
	player->startComponents(*this);
}

void Level::addPlayerProjectileAtLocation(Point position, int vel, double degrees)
{
	playerProjectiles.push_back(std::make_shared<PlayerProjectile>(position, vel, degrees));
	gameObjectBuilder_->buildPlayerProjectile(componentSystem_,"", *playerProjectiles.back());
	auto physics = playerProjectiles.back()->getComponent<PhysicsComponent>();
	physics->enableGravity(false);

	int newVelX = (int)(vel * cos(toRadians(degrees)));
	int newVelY = (int)(vel * sin(toRadians(degrees)));
	physics->setVelX(newVelX); 
	physics->setVelY(newVelY); 
	playerProjectiles.back()->startComponents(*this); 
}

void Level::addPickupAtLocation(Point position)
{
	pickups.push_back(std::make_shared<Pickup>(position));
	gameObjectBuilder_->buildItemDrop(componentSystem_, "", *pickups.back());
	pickups.back()->startComponents(*this);
}

void Level::addEnemyAtLocation(const std::string& name, Point position)
{
	enemies.push_back(std::make_shared<Enemy>(position));
	gameObjectBuilder_->buildEnemy(componentSystem_, name, *enemies.back());
	enemies.back()->startComponents(*this);
}

void Level::addTileAtLocation(int tileType, Point position)
{
	int r = position.y / Constants::TILE_SIZE;
	int c = position.x / Constants::TILE_SIZE;
	gameObjectBuilder_->buildTile(componentSystem_, tileType, tileArrangement.tiles[r][c]);
	tileArrangement.tiles[r][c].setPos(c * Constants::TILE_SIZE, r * Constants::TILE_SIZE);
	
	//Tile tile(c * Constants::TILE_SIZE, r * Constants::TILE_SIZE);
	//tileBuilder_->build(tileType, tile);
	//tileArrangement.tiles[r][c] = tile;
}

void Level::update()
{
	updateBackground();
	updateTiles();
	updatePlayer();
	updatePlayerProjectiles();
	updateEnemies();
	componentSystem_.update(*this);
}

void Level::updateBackground()
{
	//todo: be able to switch backgrounds
}

void Level::updateTiles()
{
	for (int r = 0; r < tileArrangement.rows; ++r)
		for (int c = 0; c < tileArrangement.cols; ++c)
		{
			tileArrangement.tiles[r][c].update(*this);
		}
}

void Level::updatePlayer()
{
	player->update(*this);

	oldPlayerBlock_ = Block::getBlock(player->getPos());
	oldPlayerPosInBlock_ = Point{ player->getPosX() % Constants::BLOCK_WIDTH_IN_PIXELS,
		player->getPosY() % Constants::BLOCK_HEIGHT_IN_PIXELS };

	if (!player->alive())
	{
		player->onDeath(*this);
	}
}

void Level::updatePlayerProjectiles()
{
	updateEntityVector(playerProjectiles);
}

void Level::updateEnemies()
{
	updateEntityVector(enemies);
}

void Level::render(GameWindow& window)
{
	//note order of rendering
	componentSystem_.render(*this, window);
	renderPlayer();
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

void Level::renderPlayer()
{
	player->render(*this);
}

int Level::getLevelWidth() const
{
	return tileArrangement.cols * Constants::TILE_SIZE;
}

int Level::getLevelHeight() const
{
	return tileArrangement.rows * Constants::TILE_SIZE;
}