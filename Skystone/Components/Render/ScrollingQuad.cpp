#include "ScrollingQuad.h"
#include "Resources/SpriteSheet.h"
#include "Application/GameWindow.h"
#include "Game/GameConstants.h"
#include <algorithm>

#define MOVE_FREQ 8

namespace
{
void setRect(SDL_Rect* rect, int x, int y, int w, int h) 
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}
}

ScrollingQuad::ScrollingQuad(GameObject& owner, SpriteSheet* spriteSheet)
	: RenderComponent(owner), 
	spriteSheet_(spriteSheet),
	quadrant_(Quadrant::INVALID),
	src_{0,0,0,0},
	dest_{0,0,0,0}
{
}


ScrollingQuad::~ScrollingQuad()
{
}

void ScrollingQuad::setQuadrant(Quadrant quadrant)
{
	quadrant_ = quadrant;
}

void ScrollingQuad::advance(int xBound, int yBound, Point currCam)
{
	/*
		Quadrant refers to mathmatical quadrants:       
			21
			34
	*/
	SDL_Rect* sheetRect = spriteSheet_->getFrameRect(0);
	switch (quadrant_)
	{
	case Quadrant::first:
		setRect(&src_, 0, yBound, std::max(0, (Constants::SCREEN_WIDTH+xBound)-sheetRect->w), std::min(Constants::SCREEN_HEIGHT, sheetRect->h - yBound));
		setRect(&dest_, sheetRect->w-xBound, 0, src_.w, src_.h);
		break;
	case Quadrant::second:
		setRect(&src_, xBound, yBound, std::min(Constants::SCREEN_WIDTH, sheetRect->w - xBound), std::min(Constants::SCREEN_HEIGHT, sheetRect->h - yBound));
		setRect(&dest_, 0, 0, src_.w, src_.h);
		break;
	case Quadrant::third:
		setRect(&src_, xBound, 0, std::min(Constants::SCREEN_WIDTH, sheetRect->w - xBound), std::max(0, (Constants::SCREEN_HEIGHT + yBound) - sheetRect->h));
		setRect(&dest_, 0, sheetRect->h-yBound, src_.w, src_.h);
		break;
	case Quadrant::fourth:
		setRect(&src_, 0, 0, std::max(0, (Constants::SCREEN_WIDTH+xBound)-sheetRect->w), std::max(0, (Constants::SCREEN_HEIGHT + yBound)-sheetRect->h));
		setRect(&dest_, sheetRect->w - xBound, sheetRect->h-yBound, src_.w, src_.h);
		break;
	case Quadrant::INVALID:
		break;
	}
}

void ScrollingQuad::render(GameWindow& gameWindow, float percBehind)
{
	if(quadrant_ != Quadrant::INVALID)
	{
		gameWindow.renderOnCamera(spriteSheet_->getTexture(), &src_, &dest_);
	}
}