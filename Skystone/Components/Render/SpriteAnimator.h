#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

#include "RenderComponent.h"

#include "Resources/SpriteSheet.h"
#include "GameTypes/Axis.h"

class SpriteRenderer;

class SpriteAnimator : public RenderComponent
{
public:
	SpriteAnimator(GameObject& owner, SpriteRenderer* renderer);
	virtual ~SpriteAnimator();

	virtual void start(Scene& scene);
	virtual void render(GameWindow& gameWindow, float percBehind);

	//-1 means loop forever
	void setTimesToPlay(int numLoops);

	void setSpriteSheet(const std::string& relPath);
	void setSpriteSheet(SpriteSheet* spriteSheet);
	void setSpriteIndex(int index);

	void flip(Axis axis);
	void setFlipHorz(bool value);
	void setFlipVert(bool value);

	void setRotation(double degrees);

private:
	SpriteRenderer* spriteRenderer_;
	SpriteSheet* spriteSheet_;

	int loopCount_;
	int currFrameIndex_;
	int msOnFrame_;
};

#endif //SPRITE_ANIMATOR_H
