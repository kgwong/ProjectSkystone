#include "Components/Render/ScrollingSpriteRenderer.h"
#include "Application/GameWindow.h"
#include "Game/GameConstants.h"
#include "Application/Log.h"

#define MOVE_FREQ 8 

ScrollingSpriteRenderer::ScrollingSpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet, int layerNum, bool scrollX, bool scrollY)
	: RenderComponent(owner),
	spriteSheet_{spriteSheet},
	quads{{owner, spriteSheet_},{owner, spriteSheet_},{owner, spriteSheet_},{owner, spriteSheet_}},
	sx_{scrollX}, sy_{scrollY},
	layerNum_{layerNum},
	oldCamPos_(-1, -1) // force an advance() on the first call to render() 
{
	checkDims();
	initQuads();
}

ScrollingSpriteRenderer::~ScrollingSpriteRenderer()
{
}

void ScrollingSpriteRenderer::initQuads()
{
	for (int i = 0; i < N_QUADRANTS; i++)
	{
		quads[i].setQuadrant((Quadrant)i);
	}
}

void ScrollingSpriteRenderer::render(GameWindow& gameWindow, float percBehind)
{
	if(oldCamPos_ != gameWindow.getCamera().getPos())
		advanceQuads(gameWindow);
	renderQuads(gameWindow, percBehind);
	oldCamPos_ = gameWindow.getCamera().getPos();
}

void ScrollingSpriteRenderer::checkDims()
{
	if (spriteSheet_->getFrameRect(0)->w < Constants::SCREEN_WIDTH ||
		spriteSheet_->getFrameRect(0)->h < Constants::SCREEN_HEIGHT)
	{
		LOG("Warning") << "ScrollingSpriteRenderer behavior undefined for \
			sprites < screen size";
	}
}


void ScrollingSpriteRenderer::advanceQuads(GameWindow& gameWindow)
{
	for (int i = 0; i < N_QUADRANTS; i++)
	{
		Point currCam = gameWindow.getCamera().getPos();
		quads[i].advance(findXBound(currCam), findYBound(currCam), currCam);
	}
}

void ScrollingSpriteRenderer::renderQuads(GameWindow& gameWindow, float percBehind)
{
	for (int i = 0; i < N_QUADRANTS; i++)
	{ 
		quads[i].render(gameWindow, percBehind);
	}
}

int ScrollingSpriteRenderer::findXBound(Point currCam)
{
	int maxW = spriteSheet_->getFrameRect(0)->w;
	int distTraveled = ((int)currCam.x * (int)std::pow(2, layerNum_)) / MOVE_FREQ;
	return (sx_) ? distTraveled % maxW : 0;
}

int ScrollingSpriteRenderer::findYBound(Point currCam)
{
	int maxH = spriteSheet_->getFrameRect(0)->h;
	int distTraveled = ((int)currCam.y * (int)std::pow(2,layerNum_)) / MOVE_FREQ;
	return (sy_) ? distTraveled % maxH : 0;
}