#include "SpriteAnimator.h"

#include "Resources/Resources.h"
#include "SpriteRenderer.h"

#include "Game/GameTime.h"

#include <cassert>
#include "Application/Log.h"

SpriteAnimator::SpriteAnimator(GameObject& owner, SpriteRenderer* renderer)
	:RenderComponent(owner),
	spriteRenderer_(renderer),
	spriteSheet_(renderer->getSpriteSheet()),
	loopCount_(-1),
	currFrameIndex_(0),
	msOnFrame_(0)
{
}


SpriteAnimator::~SpriteAnimator()
{
}

void SpriteAnimator::start(Scene& scene)
{
}

void SpriteAnimator::render(GameWindow& gameWindow, float percBehind)
{
	if (loopCount_ == 0)
	{
		return;
	}

	assert(loopCount_ > 0 || loopCount_ == -1);

	msOnFrame_ += Time::getElapsedRenderTime();

	int currFrameDuration = spriteSheet_->getFrameDuration(currFrameIndex_);
	while (msOnFrame_ >= currFrameDuration)
	{
		msOnFrame_ -= currFrameDuration;
		currFrameIndex_ = spriteSheet_->getNextIndex(currFrameIndex_);
		if (currFrameIndex_ == 0)
		{
			if (loopCount_ != -1)
			{
				--loopCount_;
			}
			if (loopCount_ == 0)
			{
				currFrameIndex_ = spriteSheet_->getNumFrames() - 1;
			}
		}

		currFrameDuration = spriteSheet_->getFrameDuration(currFrameIndex_);
	}

	spriteRenderer_->setSprite(Sprite{spriteSheet_, currFrameIndex_});
}

void SpriteAnimator::setTimesToPlay(int numLoops)
{
	loopCount_ = numLoops;
}

void SpriteAnimator::setSpriteSheet(const std::string& relPath)
{
	setSpriteSheet(Resources::getSpriteSheet(relPath));
}

void SpriteAnimator::setSpriteSheet(SpriteSheet* spriteSheet)
{
	spriteSheet_ = spriteSheet;
	spriteRenderer_->setSprite(Sprite{ spriteSheet, 0 });
	loopCount_ = -1;
	currFrameIndex_ = 0;
	msOnFrame_ = 0;
}

void SpriteAnimator::setSpriteIndex(int index)
{
	spriteRenderer_->setSpriteIndex(index);
	currFrameIndex_ = index;
}

void SpriteAnimator::flip(Axis axis)
{
	spriteRenderer_->flip(axis);
}

void SpriteAnimator::setFlipHorz(bool value)
{
	spriteRenderer_->setFlipHorz(value);
}

void SpriteAnimator::setFlipVert(bool value)
{
	spriteRenderer_->setFlipVert(value);
}

void SpriteAnimator::setRotation(double degrees)
{
	spriteRenderer_->setRotation(degrees);
}