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

	if (cameraChanged(gameWindow)) 
	{
		if (currCam.x <= spriteSheet_->getFrameRect(0)->w ||
			currCam.y <= spriteSheet_->getFrameRect(0)->h)
			scrollQuads(gameWindow);
		else
			scrollNonZeroRect(gameWindow);
	}
}

void ScrollingSpriteRenderer::scrollNonZeroRect(GameWindow& gameWindow)
{
	Point currCam = gameWindow.getCamera().getPos();
	// todo: add support for pictures > screen size
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
	int distTraveled = (currCam.x * layerNum_) / moveFreq_;
	return distTraveled % maxW;
}

int ScrollingSpriteRenderer::findYBound(Point currCam)
{
	int maxH = spriteSheet_->getFrameRect(0)->h;
	int distTraveled = (currCam.y * layerNum_) / moveFreq_;
	return distTraveled % maxH;
}

void ScrollingSpriteRenderer::updateCamPos(GameWindow& gameWindow)
{
	oldCameraPos_ = gameWindow.getCamera().getPos();
}
