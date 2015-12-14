#ifndef ANIMATION_RENDERER_H
#define ANIMATION_RENDERER_H

#include "RenderComponent.h"
#include "TextureSheet.h"

class GameWindow;

class AnimationRenderer : public RenderComponent
{
public:
	AnimationRenderer(GameObject& owner, TextureSheet* textureSheet);
	virtual ~AnimationRenderer();

	virtual void start(Level& level) {};
	virtual void update(Level& level);
	
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
