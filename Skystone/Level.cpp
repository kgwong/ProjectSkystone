#include "Level.h"

#include "GameConstants.h"
#include "LevelLoader.h"
#include "LevelMap.h"
#include "LevelManager.h"


Level::Level(int levelID, TextureLoader* textureLoader)
	:textureLoader_(textureLoader),
	levelManager_(nullptr),
	enemyBuilder_(nullptr),
	levelID_(levelID)
{
}

Level::~Level()
{
}

void Level::setLevelManager(LevelManager* levelManager)
{
	levelManager_ = levelManager;
}

void Level::setEnemyBuilder(EnemyBuilder* enemyBuilder)
{
	enemyBuilder_ = enemyBuilder;
}

void Level::setTileBuilder(TileBuilder* tileBuilder)
{
	tileBuilder_ = tileBuilder;
}

void Level::setPlayer(Player* p, Point newPlayerPosition)
{
	player = p;
	player->setPos(newPlayerPosition);
}

Point Level::getPlayerPos()
{
	return player->getPos();
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
	PlayerProjectile projectile(PlayerProjectile(position, vel, textureLoader_, degrees));
	projectile.callStartOnComponents(*this); //call start
	playerProjectiles.push_back(projectile);
}

void Level::addPickupAtLocation(Point position)
{
	Pickup pickup(textureLoader_);
	pickup.setPos(position);
	pickup.callStartOnComponents(*this); //call start
	pickups.push_back(pickup);
}

void Level::addEnemyAtLocation(const std::string& name, Point position)
{
	Enemy enemy(position);

	enemies.push_back(enemy);
	enemyBuilder_->build(name, enemies.back());

}

void Level::addTileAtLocation(int tileType, Point position)
{
	int r = position.y / Constants::TILE_SIZE;
	int c = position.x / Constants::TILE_SIZE;
	Tile tile(c * Constants::TILE_SIZE, r * Constants::TILE_SIZE);
	tileBuilder_->build(tileType, tile);
	tileArrangement.tiles[r][c] = tile;
}

void Level::update()
{
	updateTiles();
	updatePlayer();
	updatePlayerProjectiles();
	updateEnemies();
	updatePickups();
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

void Level::setNextLevel(Block oldBlock, Point oldPlayerPosition, Direction dir)
{
	LevelMap* levelMap = levelManager_->getLevelMap();
	Block nextBlock = levelMap->getAdjBlock(oldBlock + levelMap->getBaseBlock(levelID_), dir);
	int nextLevelID = levelMap->getLevelID(nextBlock);

	Block nextBaseBlock = levelMap->getBaseBlock(nextLevelID);
	Block newRelativeBlock{ nextBlock.r - nextBaseBlock.r,
							nextBlock.c - nextBaseBlock.c };
	

	switch (dir)
	{
	case Direction::UP:
		oldPlayerPosition.y = Constants::BLOCK_HEIGHT_IN_PIXELS - 2 * Constants::TILE_SIZE;
		break;
	case Direction::DOWN:
		oldPlayerPosition.y = 2 * Constants::TILE_SIZE;
		break;
	case Direction::LEFT:
		oldPlayerPosition.x = Constants::BLOCK_WIDTH_IN_PIXELS - 2 * Constants::TILE_SIZE;
		break;
	case Direction::RIGHT:
		oldPlayerPosition.x = 2 * Constants::TILE_SIZE;
		break;
	}


	Point newPlayerPosition{ newRelativeBlock.c * Constants::BLOCK_WIDTH_IN_PIXELS + oldPlayerPosition.x,
								newRelativeBlock.r * Constants::BLOCK_HEIGHT_IN_PIXELS + oldPlayerPosition.y};

	levelManager_->setNextLevel(nextLevelID, newPlayerPosition);

	//
	playerProjectiles.clear();
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