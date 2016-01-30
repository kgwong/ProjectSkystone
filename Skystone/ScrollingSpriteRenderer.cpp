#include "ScrollingSpriteRenderer.h"
#include "GameWindow.h"
#include "Game/GameConstants.h"
#include "Log.h"

namespace
{
	void updateRectWithCam(SDL_Rect* rect, Point camPos)
	{
		if (camPos.x <= 640)
		{
			rect->x = camPos.x;
			rect->y = camPos.y;
			rect->w = Constants::SCREEN_WIDTH;
			rect->h = Constants::SCREEN_HEIGHT;
		}
	}

	void setRect(SDL_Rect* rect, int x_, int y_, int w_, int h_)
	{
		rect->x = x_;
		rect->y = y_;
		rect->w = w_;
		rect->h = h_;
	}
}

ScrollingSpriteRenderer::ScrollingSpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet, int layerNum)
	: RenderComponent(owner), spriteSheet_{spriteSheet},
	drawSrc1_{ 0,0,Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT },
	drawSrc2_{ 0,0,0,0 },
	drawDest1_{ 0,0,Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT },
	drawDest2_{ 0,0,0,0 },
	oldCameraPos_{ 0,0 },
	layerNum_{ layerNum },
	moveFreq_{5}
{
	checkDims();
}

ScrollingSpriteRenderer::~ScrollingSpriteRenderer()
{
}

void ScrollingSpriteRenderer::render(GameWindow& gameWindow)
{
	advanceRects(gameWindow);
	gameWindow.renderOnCamera(spriteSheet_->getTexture(), &drawSrc1_, &drawDest1_);
	gameWindow.renderOnCamera(spriteSheet_->getTexture(), &drawSrc2_, &drawDest2_);
	updateCamPos(gameWindow);
}

void ScrollingSpriteRenderer::checkDims()
{

	if (drawSrc1_.w < Constants::SCREEN_WIDTH ||
		drawSrc1_.h < Constants::SCREEN_HEIGHT)
	{
		LOG << "Warning: ScrollingSpriteRenderer behavior undefined for \
			sprites < screen size";
	}
}


void ScrollingSpriteRenderer::advanceRects(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();

	if (findDelX(gameWindow) != 0)
	{
		if (currCam.x <= spriteSheet_->getFrameRect(0)->w)
			scrollBoth(gameWindow);
		else
			scrollNonZero(gameWindow);
	}
}

void ScrollingSpriteRenderer::scrollNonZero(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();
	if (drawSrc1_.w != 0)
		updateRectWithCam(&drawSrc1_, currCam);
	else
		updateRectWithCam(&drawSrc2_, currCam);
}

void ScrollingSpriteRenderer::scrollBoth(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();

	// every moveFreq_ steps the player takes, advance by layerNum_
	int maxW = spriteSheet_->getFrameRect(0)->w;
	int distTraveled = (currCam.x * layerNum_) / moveFreq_;
	int xBound = distTraveled % maxW;

	setRect(&drawSrc1_, xBound, 0, maxW - xBound, Constants::SCREEN_HEIGHT);
	setRect(&drawDest1_, 0, 0, drawSrc1_.w, Constants::SCREEN_HEIGHT);
	setRect(&drawSrc2_, 0, 0, xBound, Constants::SCREEN_HEIGHT);
	setRect(&drawDest2_, maxW - xBound, 0, drawSrc2_.w, Constants::SCREEN_HEIGHT);
}

int ScrollingSpriteRenderer::findDelX(GameWindow& gameWindow)
{
	return oldCameraPos_.x - gameWindow.getCamera().getPos().x;
}

void ScrollingSpriteRenderer::updateCamPos(GameWindow& gameWindow)
{
	oldCameraPos_ = gameWindow.getCamera().getPos();
}
