#include "SpriteRenderer.h"

#include "Application/GameWindow.h"
#include "Game/GameTime.h"

#include "Resources/Resources.h"
#include "Application/Log.h"

SpriteRenderer::SpriteRenderer(GameObject& owner, const std::string& relPath)
	:SpriteRenderer(owner, Resources::getSpriteSheet(relPath))
{
}

SpriteRenderer::SpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet)
	:RenderComponent(owner), sprite_(spriteSheet, 0),
	//currFrameIndex(0), msOnFrame(0),
	flipHorz_(false), flipVert_(false),
	rotationDegrees_(0)
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

void SpriteRenderer::setRotation(double degrees)
{
	rotationDegrees_ = degrees;
}

/*void SpriteRenderer::setSprite(const std::string& relPath)
{
	setSprite(Resources::getSpriteSheet(relPath));
}

void SpriteRenderer::setSprite(SpriteSheet* newSpriteSheet)
{
	spriteSheet_ = newSpriteSheet;
	currFrameIndex = 0;
	msOnFrame = 0;
}*/


void SpriteRenderer::setSpriteSheet(const std::string& relPath)
{
	setSpriteSheet(Resources::getSpriteSheet(relPath));
}

void SpriteRenderer::setSpriteSheet(SpriteSheet* spriteSheet)
{
	sprite_.spriteSheet = spriteSheet;
	//set sprite index too?
}

void SpriteRenderer::setSpriteIndex(int index)
{
	sprite_.index = index;
}

void SpriteRenderer::setSprite(Sprite sprite)
{
	sprite_ = sprite;
}

void SpriteRenderer::render(GameWindow& gameWindow, float percBehind)
{
	/*msOnFrame += Time::getElapsedRenderTime();
	
	int currFrameDuration = spriteSheet_->getFrameDuration(currFrameIndex);
	while (msOnFrame >= currFrameDuration)
	{
		msOnFrame -= currFrameDuration;
		currFrameIndex = spriteSheet_->getNextIndex(currFrameIndex);
		currFrameDuration = spriteSheet_->getFrameDuration(currFrameIndex);
	}
	*/

	//cleaner way to incorporate this?
	Point adjPos = RenderComponent::getRenderPosition(percBehind); 
	SDL_Rect drawDest = SDL_Rect{ (int)adjPos.x, (int)adjPos.y, getWidth(), getHeight() };

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
	gameWindow.render(sprite_.spriteSheet->getTexture(), 
					sprite_.spriteSheet->getFrameRect(sprite_.index), 
					&drawDest, 
					rotationDegrees_, 
					NULL, 
					finalFlip);
}

int SpriteRenderer::getWidth()
{
	return sprite_.getWidth();
}

int SpriteRenderer::getHeight()
{
	return sprite_.getHeight();
}
