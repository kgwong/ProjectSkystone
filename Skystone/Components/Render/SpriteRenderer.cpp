#include "SpriteRenderer.h"

#include "Application/GameWindow.h"
#include "Game/GameTime.h"

#include "Application/Log.h"

SpriteRenderer::SpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet)
	:RenderComponent(owner), spriteSheet_(spriteSheet),
	currFrameIndex(0), msOnFrame(0),
	flipHorz_(false), flipVert_(false)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::flip(Axis axis)
{
	switch (axis)
	{
	case Axis::X:
		flipVert_ = !flipVert_;
		break;
	case Axis::Y:
		flipHorz_ = !flipHorz_;
		break;
	}
}

void SpriteRenderer::setFlipHorz(bool value)
{
	flipHorz_ = value;
}

void SpriteRenderer::setFlipVert(bool value)
{
	flipVert_ = value;
}

void SpriteRenderer::setSprite(SpriteSheet* newSpriteSheet)
{
	spriteSheet_ = newSpriteSheet;
	currFrameIndex = 0;
	msOnFrame = 0;
}

void SpriteRenderer::render(GameWindow& gameWindow)
{
	msOnFrame += Time::getElapsedRenderTime();
	
	int currFrameDuration = spriteSheet_->getFrameDuration(currFrameIndex);
	while (msOnFrame >= currFrameDuration)
	{
		msOnFrame -= currFrameDuration;
		currFrameIndex = spriteSheet_->getNextIndex(currFrameIndex);
		currFrameDuration = spriteSheet_->getFrameDuration(currFrameIndex);
	}


	int frameWidth = spriteSheet_->getFrameRect(currFrameIndex)->w;
	int frameHeight = spriteSheet_->getFrameRect(currFrameIndex)->h;

	SDL_Rect drawDest = SDL_Rect{ owner_.getPosX(),
									owner_.getPosY(),
									frameWidth, frameHeight };

	SDL_RendererFlip finalFlip;
	if (flipHorz_ && flipVert_)
	{
		finalFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (flipVert_)
	{
		finalFlip = SDL_FLIP_VERTICAL;
	}
	else if (flipHorz_)
	{
		finalFlip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		finalFlip = SDL_FLIP_NONE;
	}
	gameWindow.render(spriteSheet_->getTexture(), spriteSheet_->getFrameRect(currFrameIndex), &drawDest, NULL, NULL, finalFlip);
}

int SpriteRenderer::getWidth()
{
	return spriteSheet_->getFrameRect(currFrameIndex)->w;
}

int SpriteRenderer::getHeight()
{
	return spriteSheet_->getFrameRect(currFrameIndex)->h;
}
