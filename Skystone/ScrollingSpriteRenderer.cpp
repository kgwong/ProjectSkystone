#include "ScrollingSpriteRenderer.h"
#include "GameWindow.h"
#include "GameConstants.h"
#include "Log.h"
#include <cmath>


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

	void modDrawRect(SDL_Rect* rect, int x_, int y_, int w_, int h_)
	{
		rect->x = incWithinBound(rect->x, x_, Constants::SCREEN_WIDTH);
		rect->y = incWithinBound(rect->y, y_, Constants::SCREEN_HEIGHT);
		rect->w = incWithinBound(rect->w, w_, Constants::SCREEN_WIDTH);
		rect->h = incWithinBound(rect->h, h_, Constants::SCREEN_HEIGHT);
	}

}

ScrollingSpriteRenderer::ScrollingSpriteRenderer(GameObject& owner, TextureSheet* textureSheet, int layerNum)
	: SpriteRenderer(owner, textureSheet),
	drawSrcCopy_(*drawSrc_),
	drawSrcLeft_{ 0,0,0,0 },
	drawDestLeft_{ 0, 0,0,0 },
	layerNum_{layerNum},
	oldCameraPos_{textureSheet_->getWindow()->getCamera().getPos()},
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
	if (cameraValid())
	{
		advanceRects();
	}
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), &drawSrcCopy_, &drawDest_);
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), &drawSrcLeft_, &drawDestLeft_);
	updateCamPos();
}

void ScrollingSpriteRenderer::setInitialRects()
{
	Point cameraPos = textureSheet_->getWindow()->getCamera().getPos();

	int overflow = drawSrcCopy_.w % Constants::SCREEN_WIDTH;
	// overflow is how far too left it is
	setRect(&drawSrcCopy_,
		-overflow,
		0,
		Constants::SCREEN_WIDTH + overflow,
		textureSheet_->getFull()->h);

	setRect(&drawDest_, 0, 0, drawSrcCopy_.w, drawSrcCopy_.h);

	setRect(&drawSrcLeft_, 
		Constants::SCREEN_WIDTH,
		textureSheet_->getFull()->y,
		-overflow,
		textureSheet_->getFull()->h);

	setRect(&drawDestLeft_,
		0,
		0,
		drawSrcLeft_.w,
		drawSrcLeft_.h);
}


void ScrollingSpriteRenderer::checkDims()
{
	if ((drawSrc_->w != Constants::SCREEN_WIDTH) ||
		(drawSrc_->h != Constants::SCREEN_HEIGHT))
	{
		LOG << "Warning: ScrollingSpriteRenderer behavior undefined for \
			sprites != screen size";
	}
}

void ScrollingSpriteRenderer::advanceRects()
{
	int delx = findDelX();
	modDrawRect(&drawSrcCopy_, 0, 0, -delx, 0);
	modDrawRect(&drawDest_, delx, 0, -delx, 0);

	modDrawRect(&drawSrcLeft_, -delx, 0, delx, 0);
	modDrawRect(&drawDestLeft_, 0, 0, delx, 0);
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

bool ScrollingSpriteRenderer::cameraValid()
{
	Point currCamera = textureSheet_->getWindow()->getCamera().getPos();
	int change = oldCameraPos_.x - currCamera.x;
	return std::abs(change) < 10;
}