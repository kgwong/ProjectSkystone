#include "ScrollingSpriteRenderer.h"
#include "GameWindow.h"
#include "GameConstants.h"
#include "Log.h"
#include <algorithm>

namespace
{
	void updateRectWithCam(SDL_Rect* rect, Point pos)
	{
		if (pos.x <= rect->w)
		{
			rect->x = pos.x;
			rect->y = pos.y;
		}
	}

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
}

ScrollingSpriteRenderer::ScrollingSpriteRenderer(GameObject& owner, TextureSheet* textureSheet, int layerNum)
	: SpriteRenderer(owner, textureSheet),
	drawSrc1_(*drawSrc_),
	drawSrc2_{0,0,0,0},
	drawDest2_{0,0,0,0},
	oldCameraPos_{textureSheet_->getWindow()->getCamera().getPos()},
	layerNum_{layerNum}
{
	checkDims();
}

ScrollingSpriteRenderer::~ScrollingSpriteRenderer()
{
}

void ScrollingSpriteRenderer::update(Level& level)
{
	advanceRects();
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), &drawSrc1_, &drawDest_);
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), &drawSrc2_, &drawDest2_);
	updateCamPos();
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
	Point currCam = textureSheet_->getWindow()->getCamera().getPos();

	if (findDelX() != 0)
	{
		if (currCam.x <= drawSrc_->w)
			scrollBoth();
		else
			scrollNonZero();
	}
}

void ScrollingSpriteRenderer::scrollNonZero()
{
	Point currCam = textureSheet_->getWindow()->getCamera().getPos();
	if (drawSrc1_.w != 0)
		updateRectWithCam(&drawSrc1_, currCam);
	else
		updateRectWithCam(&drawSrc2_, currCam);
}

void ScrollingSpriteRenderer::scrollBoth()
{
	Point currCam = textureSheet_->getWindow()->getCamera().getPos();
	
	int xBound = currCam.x / layerNum_;//(currCam.x / drawSrc_->w) * layerNum_;
	
	setRect(&drawSrc1_, xBound, 0, drawSrc_->w - xBound, Constants::SCREEN_HEIGHT);
	setRect(&drawDest_, 0, 0, drawSrc1_.w, Constants::SCREEN_HEIGHT);
	setRect(&drawSrc2_, 0 , 0, xBound, Constants::SCREEN_HEIGHT);
	setRect(&drawDest2_, drawSrc_->w - xBound, 0, xBound, Constants::SCREEN_HEIGHT);
}

int ScrollingSpriteRenderer::findDelX()
{
	Point currCamera = textureSheet_->getWindow()->getCamera().getPos();
	int change = oldCameraPos_.x - currCamera.x;

	if (change != 0)
		return (change > 0) ? layerNum_ : -layerNum_;
	else
		return 0;
}

void ScrollingSpriteRenderer::updateCamPos()
{
	oldCameraPos_ = textureSheet_->getWindow()->getCamera().getPos();
}
