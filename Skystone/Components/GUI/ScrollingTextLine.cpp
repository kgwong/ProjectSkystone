#include "ScrollingTextLine.h"
#include "Game/GameConstants.h"
#include "Application/Log.h"

namespace
{
}

ScrollingTextLine::ScrollingTextLine(GameObject& owner, int lineNumber, const std::string& text)
	: TextRenderer(owner), lineNumber_(lineNumber), width_(0), height_(0)
{
	TextRenderer::setText(text);
	//checkDims();
	init();
}

ScrollingTextLine::~ScrollingTextLine()
{
}

void ScrollingTextLine::scroll()
{
	owner_.setPosY(owner_.getPosY() - 1);
}

bool ScrollingTextLine::finished()
{
	return (int)owner_.getPosY() + height_ < 0;
}

void ScrollingTextLine::init()
{
	TextRenderer::setRenderMode(TextRenderer::RenderMode::RENDER_FROM_TOP_LEFT);
	setTextDims();
	float xPos = owner_.getPosX() + (Constants::SCREEN_WIDTH - width_) / 2;
	float yPos = owner_.getPosY() + (float)height_ * lineNumber_ + (float)PAD_Y * lineNumber_;
	owner_.setPos({xPos, yPos});
}

void ScrollingTextLine::setTextDims()
{
	TTF_SizeText(TextRenderer::getFont(), TextRenderer::getText().c_str() , &width_, &height_);
}

void ScrollingTextLine::checkDims()
{
	//int w, h;
	//TTF_SizeText(TextRenderer::getFont(), getText().c_str(), &w, &h);
	
	//if (w + PAD_X > Constants::SCREEN_WIDTH)
	//	LOG("WARNING") << "LINE: \"" << getText() << "\" is too long!";
}
