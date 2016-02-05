#include "Components/Render/ScrollingSpriteRenderer.h"
#include "GameWindow.h"
#include "Game/GameConstants.h"
#include "Log.h"

namespace
{
	void setRect(SDL_Rect* rect, int x_, int y_, int w_, int h_)
	{
		rect->x = x_;
		rect->y = y_;
		rect->w = w_;
		rect->h = h_;
	}
	void setRectZero(SDL_Rect* rect)
	{
		setRect(rect, 0, 0, 0, 0);
	}

	void setMaxHoriz(SDL_Rect* src, SDL_Rect* dst)
	{
		src->x = dst->x = 0;
		src->w = dst->w = Constants::SCREEN_WIDTH;
	}
	void setMaxVert(SDL_Rect* src, SDL_Rect* dst)
	{
		src->y = dst->y = 0;
		src->h = dst->h = Constants::SCREEN_HEIGHT;
	}

	void setXToBound(SDL_Rect* src, SDL_Rect* dst, int xBound)
	{
		src->x = xBound; 
		src->w = dst->w = Constants::SCREEN_WIDTH;
	}

	void setYToBound(SDL_Rect* src, SDL_Rect* dst, int yBound)
	{
		src->y = yBound; 
		src->h = dst->h = Constants::SCREEN_HEIGHT;
	}
}

ScrollingSpriteRenderer::ScrollingSpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet, int layerNum, bool scrollX, bool scrollY)
	: RenderComponent(owner), spriteSheet_{spriteSheet}, sx_{scrollX}, sy_{scrollY},
	tlS_{0,0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT},
	tlD_{0,0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT},
	trS_{0,0,0,0}, trD_{0,0,0,0},
	blS_{0,0,0,0}, blD_{0,0,0,0},
	brS_{0,0,0,0}, brD_{0,0,0,0},
	oldCameraPos_{0,0},
	layerNum_{layerNum}, 
	moveFreq_{8}
{
	checkDims();
}

ScrollingSpriteRenderer::~ScrollingSpriteRenderer()
{
}

void ScrollingSpriteRenderer::render(GameWindow& gameWindow)
{
	advanceRects(gameWindow);
	gameWindow.renderOnCamera(spriteSheet_->getTexture(), &tlS_, &tlD_);
	gameWindow.renderOnCamera(spriteSheet_->getTexture(), &trS_, &trD_);
	gameWindow.renderOnCamera(spriteSheet_->getTexture(), &blS_, &blD_);
	gameWindow.renderOnCamera(spriteSheet_->getTexture(), &brS_, &brD_);
	updateCamPos(gameWindow);
}

void ScrollingSpriteRenderer::checkDims()
{

	if (spriteSheet_->getFrameRect(0)->w < Constants::SCREEN_WIDTH ||
		spriteSheet_->getFrameRect(0)->h < Constants::SCREEN_HEIGHT)
	{
		LOG << "Warning: ScrollingSpriteRenderer behavior undefined for \
			sprites < screen size";
	}
}


void ScrollingSpriteRenderer::advanceRects(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();
	SDL_Rect* frame = spriteSheet_->getFrameRect(0);
	int endx = currCam.x + Constants::SCREEN_WIDTH;
	int endy = currCam.y + Constants::SCREEN_HEIGHT;
	if (cameraChanged(gameWindow)) 
	{
		if ( endx >= frame->w  && endy >= frame->h)
			scrollQuads(gameWindow);
		else
			scrollLargeSprite(gameWindow);
	}
}

void ScrollingSpriteRenderer::scrollLargeSprite(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();
	int xBound = findXBound(currCam);
	int yBound = findYBound(currCam);

	setRectZero(&trD_);
	setRectZero(&brD_);
	setRectZero(&blD_);

	if (sx_)
	{
		if (currCam.x + xBound <= spriteSheet_->getFrameRect(0)->w)
			setXToBound(&tlS_, &tlD_, xBound);
		else
			scrollHorizToBound(xBound);
	}
	else
		setMaxHoriz(&tlS_, &tlD_);

	if (sy_)
	{
		if (currCam.y + yBound <= spriteSheet_->getFrameRect(0)->h)
			setYToBound(&tlS_, &tlD_, yBound);
		else
			scrollVertToBound(yBound);
	}
	else
		setMaxVert(&tlS_, &tlD_);
}

void ScrollingSpriteRenderer::scrollQuads(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();
	int xBound = findXBound(currCam);
	int yBound = findYBound(currCam);
	
	advanceQuadrant(&tlS_, &tlD_, xBound, yBound, true, true);
	advanceQuadrant(&trS_, &trD_, xBound, yBound, false, true);
	advanceQuadrant(&blS_, &blD_, xBound, yBound, true, false);
	advanceQuadrant(&brS_, &brD_, xBound, yBound, false, false);
}

void ScrollingSpriteRenderer::advanceQuadrant(SDL_Rect* src, SDL_Rect* dest, int xBound, int yBound, bool left, bool top)
{
	int srcStartx, srcStarty, srcEndx, srcEndy;
	int destStartx, destStarty, destEndx, destEndy;

	srcStartx = (left) ? xBound : 0;
	srcEndx = (left) ? (Constants::SCREEN_WIDTH) : xBound;
	srcStarty = (top) ? yBound : 0;
	srcEndy = (top) ? (Constants::SCREEN_HEIGHT) : yBound;

	destStartx = (left) ? 0 : Constants::SCREEN_WIDTH-xBound;
	destEndx = (left) ? Constants::SCREEN_WIDTH-xBound : Constants::SCREEN_WIDTH;
	destStarty = (top) ? 0 : Constants::SCREEN_HEIGHT -yBound;
	destEndy = (top) ? Constants::SCREEN_HEIGHT - yBound : Constants::SCREEN_HEIGHT;

	setRect(src, srcStartx, srcStarty, srcEndx - srcStartx, srcEndy - srcStarty);
	setRect(dest, destStartx, destStarty, destEndx - destStartx, destEndy - destStarty);
}

bool ScrollingSpriteRenderer::cameraChanged(GameWindow& gameWindow)
{
	return (findDelX(gameWindow) != 0) || (findDelY(gameWindow) != 0);
}

int ScrollingSpriteRenderer::findDelX(GameWindow& gameWindow)
{
	return oldCameraPos_.x - gameWindow.getCamera().getPos().x;
}

int ScrollingSpriteRenderer::findDelY(GameWindow& gameWindow)
{
	return oldCameraPos_.y - gameWindow.getCamera().getPos().y;
}
int ScrollingSpriteRenderer::findXBound(Point currCam)
{
	int maxW = spriteSheet_->getFrameRect(0)->w;
	int distTraveled = (currCam.x * std::pow(2,layerNum_)) / moveFreq_;
	return (sx_) ? distTraveled % maxW : 0;
}

int ScrollingSpriteRenderer::findYBound(Point currCam)
{
	int maxH = spriteSheet_->getFrameRect(0)->h;
	int distTraveled = (currCam.y * std::pow(2,layerNum_)) / moveFreq_;
	return (sy_) ? distTraveled % maxH : 0;
}

void ScrollingSpriteRenderer::updateCamPos(GameWindow& gameWindow)
{
	oldCameraPos_ = gameWindow.getCamera().getPos();
}

void ScrollingSpriteRenderer::scrollHorizToBound(int xBound)
{
	tlS_.x = tlD_.x = 0;
	tlS_.w = tlD_.w = xBound;
	trS_.x = trD_.x = xBound;
	trS_.w = trD_.w = Constants::SCREEN_WIDTH - xBound;
}

void ScrollingSpriteRenderer::scrollVertToBound(int yBound)
{
	tlS_.y = tlD_.y = 0;
	tlS_.h = tlD_.w = yBound;
	blS_.x = blD_.x = yBound;
	blS_.w = blD_.w = Constants::SCREEN_HEIGHT - yBound; 
}
