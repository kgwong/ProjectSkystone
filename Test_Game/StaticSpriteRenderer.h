#ifndef STATIC_SPRITE_RENDERER_H
#define STATIC_SPRITE_RENDERER_H

#include "Sprite.h"
#include "RenderComponent.h"

class StaticSpriteRenderer : public RenderComponent
{
public:
	StaticSpriteRenderer(Sprite* sprite);
	virtual ~StaticSpriteRenderer();

	virtual void update(GameObject& owner);

	virtual int getWidth();
	virtual int getHeight();

private:
	Sprite* _sprite;
};

#endif //STATIC_SPRITE_RENDERER_H