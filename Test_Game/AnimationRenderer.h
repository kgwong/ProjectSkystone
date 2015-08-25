#ifndef ANIMATION_RENDERER_H
#define ANIMATION_RENDERER_H

#include "GameWindow.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureSheet.h"

class AnimationRenderer : public RenderComponent
{
public:
	AnimationRenderer(TextureSheet* textureSheet);
	virtual ~AnimationRenderer();

	virtual void update(GameObject& owner);
	
	virtual int getWidth();
	virtual int getHeight();

private:
	GameWindow* window_;
	TextureSheet* textureSheet_;

	int currFrame_;

	SDL_Rect* drawSrc_;
	SDL_Rect drawDest_;

private:
	void incrementFrame();
};

#endif //RENDERCOMPONENT_H
