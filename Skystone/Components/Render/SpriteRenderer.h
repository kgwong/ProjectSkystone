#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Resources/SpriteSheet.h"

#include "RenderComponent.h"
#include "GameTypes/Axis.h"

class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet);
	virtual ~SpriteRenderer();

	void flip(Axis axis);
	void setFlipHorz(bool value);
	void setFlipVert(bool value);

	void setSprite(SpriteSheet* newSpriteSheet);

	void render(GameWindow& gameWindow);

	virtual int getWidth();
	virtual int getHeight();

private:
	SpriteSheet* spriteSheet_;

	int currFrameIndex;
	int msOnFrame;

	bool flipHorz_, flipVert_; 
};

#endif //SPRITE_RENDERER_H