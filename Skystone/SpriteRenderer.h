#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "RenderComponent.h"
#include "TextureSheet.h"

class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(GameObject& owner, TextureSheet* textureSheet);
	SpriteRenderer(GameObject& owner, TextureSheet* textureSheet,
		int textureIndex);

	virtual ~SpriteRenderer();

	virtual void start(Level& level) {};
	virtual void update(Level& level);

	virtual int getWidth();
	virtual int getHeight();

public: ///
	TextureSheet* textureSheet_;

	SDL_Rect* drawSrc_;
	SDL_Rect drawDest_;
};

#endif //SPRITE_RENDERER_H