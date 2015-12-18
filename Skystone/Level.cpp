#include "Level.h"

#include "GameConstants.h"
#include "LevelLoader.h"
#include "LevelMap.h"
#include "LevelManager.h"
#include "TextureLoader.h"
#include "EnemyBuilder.h"
#include "TileBuilder.h"

#include "SpriteRenderer.h"

#include "PhysicsComponent.h" //
#include "CircleMath.h" //

Level::Level(int levelID)
	:player(nullptr),
	levelManager_(nullptr),
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
	player->registerComponents(componentSystem_);
	startEntityComponents();
}

void Level::onExit()
{
	player->disownComponents();
	for (auto& p : playerProjectiles)
		p->disownComponents();
	playerProjectiles.clear();
	componentSystem_.cleanup();
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
	background_ = std::make_shared<GameObject>();
	background_->setType(GameObject::Type::BACKGROUND);
	background_->addComponent(componentSystem_.getNew<SpriteRenderer>(*background_, gameObjectBuilder_->getTexture("Assets/backgroundTest.png")));
}

void Level::setPlayer(GameObject* p, Point startPosition)
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
	auto n = gameObjectBuilder_->buildPlayerProjectile(componentSystem_, "");
	n->setPos(position);
	playerProjectiles.push_back(n);
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
	auto n = gameObjectBuilder_->buildItemDrop(componentSystem_, "");
	n->setPos(position);
	drops.push_back(n);
	drops.back()->startComponents(*this);
}

void Level::addEnemyAtLocation(const std::string& name, Point position)
{
	auto n = gameObjectBuilder_->buildEnemy(componentSystem_, name);
	n->setPos(position);
	enemies.push_back(n);
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

void Level::handleInput(SDL_Event& e)
{
	componentSystem_.handleInput(e);
}

void Level::update()
{
	updatePlayer();
	componentSystem_.update(*this);
	removeDeadObjects(drops);
	removeDeadObjects(enemies);
	removeDeadObjects(playerProjectiles);
}

void Level::startComponents(std::vector<std::shared_ptr<GameObject>>& v)
{
	for (auto& obj : v)
		obj->startComponents(*this);
}

void Level::removeDeadObjects(std::vector<std::shared_ptr<GameObject>>& v)
{
	for (size_t i = 0; i < v.size(); /*empty*/)
	{
		auto& obj = v[i];
		if (!obj->alive())
		{
			obj->broadcastEvent(ComponentEvent(ComponentEvent::Type::onDeath, *this));
			ComponentSystem::vector_remove(v, i);
		}
		else
		{
			++i;
		}
	}
}

void Level::updatePlayer()
{
	oldPlayerBlock_ = Block::getBlock(player->getPos());
	oldPlayerPosInBlock_ = Point{ player->getPosX() % Constants::BLOCK_WIDTH_IN_PIXELS,
		player->getPosY() % Constants::BLOCK_HEIGHT_IN_PIXELS };

	if (!player->alive())
	{
		player->broadcastEvent(ComponentEvent(ComponentEvent::Type::onDeath, *this));
	}
}

void Level::render(GameWindow& window)
{
	componentSystem_.render(*this, window);
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

int Level::getLevelWidth() const
{
	return tileArrangement.cols * Constants::TILE_SIZE;
}

int Level::getLevelHeight() const
{
	return tileArrangement.rows * Constants::TILE_SIZE;
}