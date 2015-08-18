#include "StaticSpriteRenderer.h"

StaticSpriteRenderer::StaticSpriteRenderer(Sprite* sprite)
	:_sprite(sprite)
{
}


StaticSpriteRenderer::~StaticSpriteRenderer()
{
}

void StaticSpriteRenderer::update(GameObject& owner)
{
	_sprite->render(owner.getPos());
}

int StaticSpriteRenderer::getWidth()
{
	return _sprite->getWidth();
}

int StaticSpriteRenderer::getHeight()
{
	return _sprite->getHeight();
}