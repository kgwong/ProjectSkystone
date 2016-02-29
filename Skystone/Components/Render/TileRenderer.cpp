#include "TileRenderer.h"

#include "Game/GameConstants.h"

TileRenderer::TileRenderer(GameObject& owner, SpriteSheet* spriteSheet, int tileNum)
	:RenderComponent(owner), spriteSheet_(spriteSheet), tileNum_(tileNum)
{
}

TileRenderer::~TileRenderer()
{
}

void TileRenderer::render(GameWindow& gameWindow, float percBehind)
{
	Point adjPos = RenderComponent::getRenderPosition(percBehind);
	//explicitly converting to int
	SDL_Rect dst = { (int)adjPos.x, (int)adjPos.y, Constants::TILE_SIZE, Constants::TILE_SIZE };
	gameWindow.render(spriteSheet_->getTexture(), spriteSheet_->getFrameRect(tileNum_), &dst);
}

int TileRenderer::getWidth()
{
	return Constants::TILE_SIZE;
}

int TileRenderer::getHeight()
{
	return Constants::TILE_SIZE;
}
