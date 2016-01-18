#include "ScrollingSpriteRenderer.h"
#include "GameWindow.h"
#include "GameConstants.h"
#include "Log.h"
#include <algorithm>

namespace
{
	void setRect(SDL_Rect* rect, int x_, int y_, int w_, int h_)
	{
		rect->x = x_;
		rect->y = y_;
		rect->w = w_;
		rect->h = h_;
	}

	int incWithinBound(int val, int changeBy, int max)
	{
		if (val + changeBy < 0)
			return max;
		else if (val + changeBy > max)
			return 0;
		else
			return val + changeBy;
	}

	void modDrawRect(SDL_Rect* rect, int x_, int y_, int w_, int h_, int maxW)
	{
		rect->x = incWithinBound(rect->x, x_, maxW);
		rect->y = incWithinBound(rect->y, y_, Constants::SCREEN_HEIGHT);
		rect->w = incWithinBound(rect->w, w_, maxW); 
		rect->h = incWithinBound(rect->h, h_, Constants::SCREEN_HEIGHT);	
	}

	void modNonZeroDrawRect(SDL_Rect* rect, int x_, int y_, int w_, int h_, int maxW)
	{
		if (rect->w != 0 && rect->h != 0)
			modDrawRect(rect, x_, y_, w_, h_, maxW);
	}

}

ScrollingSpriteRenderer::ScrollingSpriteRenderer(GameObject& owner, TextureSheet* textureSheet, int layerNum)
	: SpriteRenderer(owner, textureSheet),
	drawSrc1_(*drawSrc_),
	drawSrc2_{ 0,0,0,0 },
	drawDest2_{ 0, 0,0,0 },
	oldCameraPos_{textureSheet_->getWindow()->getCamera().getPos()},
	layerNum_{layerNum},
	scale_{2}
{
	checkDims();
	setInitialRects();
}

ScrollingSpriteRenderer::~ScrollingSpriteRenderer()
{
}

void ScrollingSpriteRenderer::update(Level& level)
{
	Point currCamera = textureSheet_->getWindow()->getCamera().getPos();
	advanceRects();
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), &drawSrc1_, &drawDest_);
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), &drawSrc2_, &drawDest2_);
	updateCamPos();
}

void ScrollingSpriteRenderer::setInitialRects()
{
	Point cameraPos = textureSheet_->getWindow()->getCamera().getPos();
	// uses the camera value from the last level
	int overflow = drawSrc1_.w % Constants::SCREEN_WIDTH;
	// overflow is how far too left it is
	
	setRect(&drawSrc1_,
		-overflow,
		0,
		Constants::SCREEN_WIDTH + overflow,
		std::min<int>(textureSheet_->getFull()->h, Constants::SCREEN_HEIGHT));

	setRect(&drawDest_, 0, 0, drawSrc1_.w, drawSrc1_.h);

	setRect(&drawSrc2_,
		drawSrc_->w,
		0,
		-overflow,
		std::min<int>(textureSheet_->getFull()->h, Constants::SCREEN_HEIGHT));
	setRect(&drawDest2_,
		0,
		0,
		drawSrc2_.w,
		drawSrc2_.h);
}


void ScrollingSpriteRenderer::checkDims()
{
	if (drawSrc_->w < Constants::SCREEN_WIDTH || 
		drawSrc_->h < Constants::SCREEN_HEIGHT)
	{
		LOG << "Warning: ScrollingSpriteRenderer behavior undefined for \
			sprites < screen size";
	}
}

void ScrollingSpriteRenderer::advanceRects()
{
	int delx = findDelX();
	int maxW = drawSrc_->w;

	if (rectAtEdge(delx)) 
	{
    	modDrawRect(&drawSrc1_, 0, 0, -delx, 0, maxW);
		modDrawRect(&drawDest_, delx, 0, -delx, 0, maxW);

		modDrawRect(&drawSrc2_, -delx, 0, delx, 0, maxW);
		modDrawRect(&drawDest2_, 0, 0, delx, 0, maxW);
	}
	else
	{
		modNonZeroDrawRect(&drawSrc1_, -delx, 0, 0, 0, maxW);
		modNonZeroDrawRect(&drawDest_, 0, 0, 0, 0, maxW);

		modNonZeroDrawRect(&drawSrc2_, -delx, 0, 0, 0, maxW);
		modNonZeroDrawRect(&drawDest2_, 0, 0, 0, 0, maxW);
	}
}

int ScrollingSpriteRenderer::findDelX()
{
	Point currCamera = textureSheet_->getWindow()->getCamera().getPos();
	int change = oldCameraPos_.x - currCamera.x;
	if (std::abs(change) > 0)
		return (change > 0) ? layerNum_ : -layerNum_;
	else
		return change;
}

void ScrollingSpriteRenderer::updateCamPos()
{
	oldCameraPos_ = textureSheet_->getWindow()->getCamera().getPos();
}

bool ScrollingSpriteRenderer::rectAtEdge(int dx)
{
	int maxW = drawSrc_->w;

	bool firstRect = (drawSrc1_.x - dx) < 0 || (drawSrc1_.x + dx < 0);
	bool secondRect = (drawSrc2_.x - dx) < 0 || (drawSrc2_.x + dx) < 0;
	return firstRect || secondRect;
}