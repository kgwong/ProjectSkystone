#include "Sprite.h"


Sprite::Sprite()
	: Sprite(nullptr, -1)
{
}

Sprite::Sprite(SpriteSheet* newSpriteSheet, int newIndex)
	: spriteSheet(newSpriteSheet), index(newIndex)
{
}

int Sprite::getWidth()
{
	return spriteSheet->getFrameRect(index)->w;
}

int Sprite::getHeight()
{
	return spriteSheet->getFrameRect(index)->h;
}
