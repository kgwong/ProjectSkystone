#include "Level.h"

#include "Resources.h"


Level::Level(GameWindow* window, TileSet* tileSet) //
	:_window(window), _tileSet(tileSet), enemySprite(window, "Enemies/enemy.png"), _tileSize(tileSet->getTileSize())
{

	Enemy newEnemy(_window, &enemySprite);
	newEnemy.setPos(660, 660);
	enemies.push_back(newEnemy);

	Enemy newEnemy1(_window, &enemySprite);
	newEnemy1.setPos(630, 660);
	enemies.push_back(newEnemy1);

	Enemy newEnemy2(_window, &enemySprite);
	newEnemy2.setPos(444, 444);
	enemies.push_back(newEnemy2);

	Enemy newEnemy3(_window, &enemySprite);
	newEnemy3.setPos(333, 333);
	enemies.push_back(newEnemy3);
}


Level::~Level()
{
}

void Level::load(const std::string& filepath)
{
	std::ifstream map(getLevelsPath(filepath)); //should probably do more error checking
	if (map == nullptr)
		std::cout << "Loading Level failed!" << std::endl;

	map >> _numTilesWide >> _numTilesHigh;

	tileArrangement = std::vector<std::vector<Tile>>(_numTilesHigh, std::vector<Tile>(_numTilesWide));

	for (int y = 0; y < _numTilesHigh; ++y)
	{
		for (int x = 0; x < _numTilesWide; ++x)
		{
			int tileNum;
			map >> tileNum;
			tileArrangement[y][x] = _tileSet->createTile(tileNum, x, y);
		}
	}
}

void Level::update()
{
	updatePlayerProjectiles();
}

void Level::updatePlayerProjectiles()
{
	std::cout << playerProjectiles.size() << std::endl;
	for (auto i = playerProjectiles.begin(); i != playerProjectiles.end(); ++i)
	{
		i->update();
	}
}


void Level::render()
{
	renderTiles();
	renderEnemies();
	renderPlayerProjectiles();
}

void Level::renderTiles() 
{
	for (int y = 0; y < _numTilesHigh; ++y)
		for (int x = 0; x < _numTilesWide; ++x)
			tileArrangement[y][x].render();
}

void Level::renderEnemies()
{
	for (auto i = enemies.begin(); i < enemies.end(); ++i)
		i->draw();
}

void Level::renderPlayerProjectiles()
{
	for (auto i = playerProjectiles.begin(); i != playerProjectiles.end(); ++i)
	{
		i->draw();
	}
}

int Level::getLevelWidth() const
{
	return _numTilesWide * _tileSet->getTileSize();
}

int Level::getLevelHeight() const
{
	return _numTilesHigh * _tileSet->getTileSize();
}

int Level::getTileSize() const
{
	return _tileSize;
}
