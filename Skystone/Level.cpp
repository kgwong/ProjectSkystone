#include "Level.h"

#include "GameConstants.h"
#include "LevelLoader.h"
#include "LevelMap.h"
#include "LevelManager.h"
#include "TextureLoader.h"
#include "EnemyBuilder.h"
#include "TileBuilder.h"
#include "Background.h"

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
	background_ = std::make_shared<Background>(spriteRenderer);
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
			tileArrangement.tiles[r][c].callStartOnComponents(*this);
	player->callStartOnComponents(*this);
	startComponents(playerProjectiles);
	startComponents(enemies);
	startComponents(pickups);
}

void Level::addPlayerProjectileAtLocation(Point position, int vel, double degrees)
{
	playerProjectiles.push_back(PlayerProjectile(position, vel, degrees));
	gameObjectBuilder_->buildPlayerProjectile("", playerProjectiles.back());
	playerProjectiles.back().callStartOnComponents(*this); 

}

void Level::addPickupAtLocation(Point position)
{
	pickups.push_back(Pickup(position));
	gameObjectBuilder_->buildItemDrop("", pickups.back());
	pickups.back().callStartOnComponents(*this);
}

void Level::addEnemyAtLocation(const std::string& name, Point position)
{
	enemies.push_back(Enemy(position));
	gameObjectBuilder_->buildEnemy(name, enemies.back());
	enemies.back().callStartOnComponents(*this);
}

void Level::addTileAtLocation(int tileType, Point position)
{
	int r = position.y / Constants::TILE_SIZE;
	int c = position.x / Constants::TILE_SIZE;
	gameObjectBuilder_->buildTile(tileType, tileArrangement.tiles[r][c]);
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
	updatePickups();
}

void Level::updateBackground()
{
	//todo: be able to switch backgrounds
}

void Level::updateTiles()
{
	for (int r = 0; r < tileArrangement.rows; ++r)
		for (int c = 0; c < tileArrangement.cols; ++c)
			tileArrangement.tiles[r][c].update(*this);
}

void Level::updatePlayer()
{
	player->update(*this);

	oldPlayerBlock_ = Block::getBlock(player->getPos());
	oldPlayerPosInBlock_ = Point{ player->getPosX() % Constants::BLOCK_WIDTH_IN_PIXELS,
		player->getPosY() % Constants::BLOCK_HEIGHT_IN_PIXELS };

	if (player->isDead())
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

void Level::updatePickups()
{
	updateEntityVector(pickups);
}

void Level::render()
{
	//note order of rendering
	renderBackground();
	renderTiles();
	renderEnemies();
	renderPlayerProjectiles();
	renderPlayer();
	renderPickups();
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

void Level::renderTiles() 
{
	for (int r = 0; r < tileArrangement.rows; ++r)
		for (int c = 0; c < tileArrangement.cols; ++c)
			tileArrangement.tiles[r][c].render(*this);
}

void Level::renderEnemies()
{
	renderEntityVector(enemies);
}

void Level::renderPlayerProjectiles()
{
	renderEntityVector(playerProjectiles);
}

void Level::renderPickups()
{
	renderEntityVector(pickups);
}

void Level::renderBackground()
{
	background_->render(*this);
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