#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "RenderComponent.h"


class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(GameWindow* window, 
		SDL_Texture* texture, 
		SDL_Rect drawSrc);
	virtual ~SpriteRenderer();

	virtual void update(GameObject& owner);

	virtual int getWidth();
	virtual int getHeight();

private:
	GameWindow* window_;
	SDL_Texture* texture_;
	SDL_Rect drawSrc_;

	SDL_Rect drawDest_;


};

#endif //SPRITE_RENDERER_H