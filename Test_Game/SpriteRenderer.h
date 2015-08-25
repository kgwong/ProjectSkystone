#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "RenderComponent.h"
#include "TextureSheet.h"


class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(TextureSheet* textureSheet);

	SpriteRenderer(TextureSheet* textureSheet,
		int textureIndex);

	virtual ~SpriteRenderer();

	virtual void update(GameObject& owner);

	virtual int getWidth();
	virtual int getHeight();

private:
	TextureSheet* textureSheet_;

	SDL_Rect* drawSrc_;

	SDL_Rect drawDest_;


};

#endif //SPRITE_RENDERER_H