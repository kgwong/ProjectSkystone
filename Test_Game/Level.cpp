#include "Level.h"

#include "LevelLoader.h"
#include "MainGame.h"

Level::Level(MainGame* mainGame, GameWindow* window, ResourceLocator* resourceLocator)
	:_mainGame(mainGame),
	_window(window), 
	_resourceLocator(resourceLocator),
	_enemyBuilder(_resourceLocator)
{
	addPickupAtLocation(Point(100, 100));
}



Level::~Level()
{
}

void Level::load(const std::string& filepath, TileSet* tileSet)
{
	LevelLoader::loadTiles(filepath + "Tiles", *this, tileSet);
	LevelLoader::loadEnemies(filepath + "Enemies", *this);

}

void Level::setPlayer(Player* p)
{
	player = p;
	player->setPos(getLevelWidth()/ 2 + 100, getLevelHeight() / 2);
}

void Level::changeLevel(int levelID)
{
	_mainGame->changeLevel(levelID);
}

void Level::addPlayerProjectileAtLocation(Point position, int vel, Direction dir)
{
	playerProjectiles.push_back( PlayerProjectile(position, vel, _resourceLocator->getAnimation("Assets/Animations/playerProjectile.png"), dir) );
}

void Level::addPickupAtLocation(Point position)
{
	Pickup pickup(_resourceLocator->getSprite("Assets/Pickups/pickup.png"));
	pickup.setPos(position);
	pickups.push_back(pickup);
}

void Level::addEnemyAtLocation(const std::string& name, Point position)
{
	Enemy* enemy = _enemyBuilder.create(name);
	enemy->setPos(position);
	enemies.push_back(*enemy);
	delete enemy;//
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
			tileArrangement.tiles[r][c].update();
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

void Level::renderTiles() 
{
	for (int r = 0; r < tileArrangement.rows; ++r)
		for (int c = 0; c < tileArrangement.cols; ++c)
			tileArrangement.tiles[r][c].render();
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
	player->render();
}

int Level::getLevelWidth() const
{
	return tileArrangement.cols * tileArrangement.tileSize;
}

int Level::getLevelHeight() const
{
	return tileArrangement.rows * tileArrangement.tileSize;
}