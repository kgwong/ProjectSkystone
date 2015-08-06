#include "Level.h"

#include "LevelLoader.h"

Level::Level(GameWindow* window, ResourceLocator* resourceLocator) 
	:_window(window), _resourceLocator(resourceLocator),
	_enemyBuilder(_resourceLocator)
{
	addPickupAtLocation(Point(100, 100));

	addEnemyAtLocation("", Point(660, 660));
	addEnemyAtLocation("", Point(630, 660));
	addEnemyAtLocation("", Point(444, 444));
	addEnemyAtLocation("", Point(333, 333));

	addEnemyAtLocation("strong", Point(563, 300));
}

Level::~Level()
{
}

void Level::load(const std::string& filepath, TileSet* tileSet)
{
	tileArrangement = LevelLoader::load(filepath, tileSet);
}

void Level::setPlayer(Player* p)
{
	player = p;
}

void Level::addPlayerProjectileAtLocation(Point position, int vel, Direction dir)
{
	playerProjectiles.push_back( PlayerProjectile(position, vel, _resourceLocator->getAnimation("Assets/Animations/playerProjectile.png"), dir) );
};

void Level::addPickupAtLocation(Point position)
{
	Pickup pickup(_resourceLocator->getSprite("Assets/Pickups/pickup.png"));
	pickup.setPos(position);
	pickups.push_back(pickup);
};

void Level::addEnemyAtLocation(const std::string& name, Point position)
{
	Enemy* enemy = _enemyBuilder.create(name);
	enemy->setPos(position);
	enemies.push_back(*enemy);
	delete enemy;//
};

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
	for (int r = 0; r < tileArrangement._rows; ++r)
		for (int c = 0; c < tileArrangement._cols; ++c)
			tileArrangement._tiles[r][c].update();
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
	for (int r = 0; r < tileArrangement._rows; ++r)
		for (int c = 0; c < tileArrangement._cols; ++c)
			tileArrangement._tiles[r][c].render();
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
	return tileArrangement._cols * tileArrangement._tileSize;
}

int Level::getLevelHeight() const
{
	return tileArrangement._rows * tileArrangement._tileSize;
}